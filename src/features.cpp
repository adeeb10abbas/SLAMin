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
 cv::Mat mask;
 // Computing F matrix using RANSAC
  cv::Mat E = cv::findEssentialMat(
          src_pts, dst_pts, // matching points
          cv::Mat_<double>::eye(3,3),
          cv::RANSAC, 0.999, 1.0, mask); // distance
    cout <<  E << endl;
  
  // Recovering Pose
  cv::Mat R, t;
  cv::recoverPose(E, src_pts, dst_pts, cv::Mat_<double>::eye(3,3), R, t, mask);
  // We get the rotation and translation out of here.
  
  
return E;
}
// void featureProcessing::tranRotEssential(Mat& image, Mat& fundamental) {
//   Mat w;
//   cv::SVD::compute(essential, w);
// }


/* What I want to do today - 
1) Figure out what to do with the Fundamental Matrix and the Mask
2) Implement the whole thing
3) Work on Visualization of 3d points in Open3D
*/

// A function to draw some bs from the fundamental matrix? 
static void Draw(string window_name, int height, int width, int left, int top){
// const double max_z = 1.0e4;
// 	for (int y = 0; y < xyz.rows; y++)
// 	{
// 		for (int x = 0; x < xyz.cols; x++)
// 		{
// 			Vec3f point = xyz.at<Vec3f>(y, x);
// 			if (fabs(point[2] - max_z) < FLT_EPSILON || fabs(point[2]) > max_z) continue;

// 			double X = point[0];
// 			double Y = point[1];
// 			double Z = point[2];

// 			//pcl::PointXYZRGB rgbPoint;
// 			pcl::PointXYZ rgbPoint;
// 			rgbPoint.x = X;
// 			rgbPoint.y = Y;
// 			rgbPoint.z = Z;

// 			//Vec3b colorLeft = img1.at<Vec3b>(y, x);

// 			//uint32_t rgb = (static_cast<uint32_t>(colorLeft.val[2]) << 16 |
// 			//	static_cast<uint32_t>(colorLeft.val[1]) << 8 | static_cast<uint32_t>(colorLeft.val[0]));
// 			//rgbPoint.rgb = *reinterpret_cast<float*>(&rgb);

// 			point_cloud->points.push_back(rgbPoint);
// 		}
// 	}
}
