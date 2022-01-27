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
    // Generate ORBs from keypoints
    std::vector<cv::KeyPoint> keypoints;
    cv::KeyPoint::convert(corners, keypoints); 

    detector_->compute(image, keypoints, descriptors); // calculate descriptors from keypoints here
    std::vector<std::vector<DMatch>> matches;
    std::vector<std::vector<DMatch>> good_matches;
    if (!prev_.desc.empty()) {
      matcher_.knnMatch(descriptors, prev_.desc, matches, 2); //matching done. 
    }
    
    for (vector<vector<cv::DMatch> >::iterator matchIterator= matches.begin();
         matchIterator!= matches.end(); ++matchIterator) {
        if ((*matchIterator)[0].distance < 0.7f * (*matchIterator)[1].distance) {
            good_matches.push_back((*matchIterator)[0]);
        }
    }

    prev_.kps = keypoints;
    prev_.desc = descriptors; 

    vector<cv::Point2f> src_pts, dst_pts;
    for (vector<cv::DMatch>::iterator it= good_matches.begin();
         it!= good_matches.end(); ++it)
    {
        // Get the position of left keypoints
        float x= keypoints[it->queryIdx].pt.x;
        float y= keypoints[it->queryIdx].pt.y;
        src_pts.push_back(cv::Point2f(x,y));
        // Get the position of right keypoints
        float x_= prev_.kps[it->trainIdx].pt.x;
        float y_= prev_.kps[it->trainIdx].pt.y;
        dst_pts.push_back(cv::Point2f(x_,y_));
    }

    // auto _test_ = calculateCamMat(image, prev_.kps, keypoints);
    return keypoints;
  }
//points 1 and point 2 would be - prev_.keypoints and keypoints 

Mat featureProcessing::calculateCamMat (const Mat& image, std::vector<cv::KeyPoint>& points1,
                    std::vector<cv::KeyPoint>& points2) {
  std::vector<Point2f> src_pts;
  std::vector<Point2f> dst_pts;
  cv::KeyPoint::convert(points1, src_pts);
  cv::KeyPoint::convert(points2, dst_pts);
 // Calculating the middle of the image.
 int x = image.size().width/2;
 int y = image.size().height/2;
 
 //Focal Lenghts
 double fov = 80 * (M_PI/180);
 double f_x = x / tan(fov/2);
 double f_y = y / tan(fov/2);
 
 // Computing F matrix using RANSAC
  // cv::Mat fundamental = cv::findFundamentalMat(
  //         cv::Mat(src_pts), cv::Mat(dst_pts), // matching points
  //         FM_RANSAC,  // RANSAC method
  //         5.0); // distance

// cout << fundamental << std::endl;
cv::Mat fundamental;
return fundamental;
}