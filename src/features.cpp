#include "iostream"
#include "features.hpp"
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
    // Now we have both keypoints and descriptors for this frame. {kps, descriptors}

    // [DONE] do some matching and then return kps and des cv2.BFMatcher()
    // [DONE] and draw them on the frame 
    // read this - https://docs.opencv.org/3.4/dc/dc3/tutorial_py_matcher.html
    // put this in the CPP file not the header lmao
    std::vector<std::vector<DMatch>> matches;
    if (!prev_.desc.empty())
    {
      matcher_.knnMatch(descriptors, prev_.desc, matches, 2); //matching done. 
    }
    
    prev_.kps = keypoints;
    prev_.desc = descriptors; 

    return keypoints;
  }