#include "iostream"
#include "features.hpp"
#include <math.h>
#include <pcl/io/pcd_io.h>
# include <Eigen/Core>

std::vector<cv::KeyPoint> featureProcessing::processImage(Mat& image){
    std::vector<cv::Point2f> corners;
    Mat descriptors;
    cv::goodFeaturesToTrack(image, corners, 3000, 0.01, 4);
    // Add some documentation about what these args mean.
    vector<cv::Point2f> src_pts, dst_pts;
    // Generate ORBs from keypoints
    std::vector<cv::KeyPoint> keypoints;

    cv::KeyPoint::convert(corners, keypoints); 
    // calculate descriptors from keypoints here
    detector_->compute(image, keypoints, descriptors);
    
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
//TODO:There's probably a better way to do this. 

Mat featureProcessing::calculateCamMat (const Mat& image, std::vector<Point2f> src_pts,
                    std::vector<Point2f> dst_pts) {
 // Calculating the middle of the image.
 int x = image.size().width/2;
 int y = image.size().height/2;
 
 //Focal Lenghts
 double fov = 80 * (M_PI/180);
 double f_x = x / tan(fov/2);
 double f_y = y / tan(fov/2);
 cv::Mat mask;
 // Computing F matrix using RANSAC
  cv::Mat E = cv::findEssentialMat(
          src_pts, dst_pts, // matching points
          cv::Mat_<double>::eye(3,3),
          cv::RANSAC, 0.999, 1.0, mask); // distance
    // cout <<  E << endl;
  
  // Recovering Pose
  cv::Mat R, t;
  
  cv::recoverPose(E, src_pts, dst_pts, cv::Mat_<double>::eye(3,3), R, t, mask);
  // We get the rotation and translation out of here.
  
  // cout << "R: " << R << endl;
  // Mat b= Mat::zeros();
  Mat I = Mat_<double>::eye(3,3);
  auto r_ = R*I;
  // cout << "R: " << r_ << endl;
  vector<double> camera_coords = {t.at<double>(0,0), t.at<double>(0,1), t.at<double>(0,2)};
  cout << camera_coords.at(0) << endl; // Work on 
  // auto R_ = Eigen::Matrix4d::Identity();
  
return E;
}

// Start plotting the camera_coordinates in the visualizer in PCL on another thread. 
// Should be fun. 
