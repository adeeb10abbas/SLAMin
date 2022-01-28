#include "iostream"
#include "features.hpp"
#include <math.h>
using namespace cv;
/**
 * @brief Takes in a frame from a video and computes the keypoint 
 * and descripter using the FAST algorithm. Check - ]
 * https://docs.opencv.org/4.x/df/dd2/tutorial_py_surf_intro.html 
 * 
 * @param image1 
 * @return void 
 */

std::vector<cv::KeyPoint> featureProcessing::processImage(Mat& image){
    std::vector<cv::Point2f> corners;
    Mat descriptors;
    cv::goodFeaturesToTrack(image, corners, 3000, 0.01, 4);
    vector<cv::Point2f> src_pts, dst_pts;
    // Generate ORBs from keypoints
    std::vector<cv::KeyPoint> keypoints;
    cv::KeyPoint::convert(corners, keypoints); 

    detector_->compute(image, keypoints, descriptors); // calculate descriptors from keypoints here
    
    std::vector<vector<DMatch>> matches;
    std::vector<DMatch> good_matches;
    
    if (!prev_.desc.empty()) {
      matcher_.knnMatch(descriptors, prev_.desc, matches, 2); //matching done. 
      
      for (int i = 0; i < matches.size(); i++) {
        if (matches.at(i)[0].distance<0.7f *(matches.at(i)[1].distance)) {
          good_matches.emplace_back(matches.at(i)[0]);
          }
        }

      for (int i = 0; i < good_matches.size(); i++) {
        src_pts.push_back(keypoints[good_matches[i].queryIdx].pt);
        dst_pts.push_back(prev_.kps[good_matches[i].trainIdx].pt);
      }
      auto _test_ = calculateCamMat(image, src_pts, dst_pts);
    }

    prev_.kps = keypoints;
    prev_.desc = descriptors; 

    
    return keypoints;
  }
//points 1 and point 2 would be - prev_.keypoints and keypoints 
Mat featureProcessing::calculateCamMat (const Mat& image, std::vector<Point2f> src_pts,
                    std::vector<Point2f> dst_pts) {
 // Calculating the middle of the image.
 int x = image.size().width/2;
 int y = image.size().height/2;
 
 //Focal Lenghts
 double fov = 80 * (M_PI/180);
 double f_x = x / tan(fov/2);
 double f_y = y / tan(fov/2);

 // Computing F matrix using RANSAC
  cv::Mat fundamental = cv::findFundamentalMat(
          cv::Mat(src_pts),cv::Mat(dst_pts), // matching points
          FM_RANSAC,  // RANSAC method
          5.0); // distance
    cout <<  fundamental << endl;

// cv::Mat fundamental;
return fundamental;
}