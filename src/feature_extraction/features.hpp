#pragma once
#include <vector>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/ocl.hpp>

// using cv::xfeatures2d::BriefDescriptorExtractor;
// using cv::xfeatures2d::SURF;
// using cv::xfeatures2d::DAISY;
// using cv::xfeatures2d::FREAK;

using namespace cv;
using namespace std;

struct kpDesc {
  std::vector<cv::KeyPoint> kps;
  Mat desc;
};

class featureProcessing{
 public:
   featureProcessing(){}
   std::vector<cv::KeyPoint> processImage(Mat& image) {
    std::vector<cv::Point2f> corners;
    Mat descriptors;
    cv::goodFeaturesToTrack(image, corners, 3000, 0.01, 4);
    // Generate ORBs from keypoints
    std::vector<cv::KeyPoint> keypoints;
    #pragma omp for
    for (size_t i = 0; i < corners.size() ; i++)
    {
      keypoints.emplace_back(KeyPoint(corners.at(i), 1));
    }
    detector_->compute(image, keypoints, descriptors); // calculate descriptors from keypoints here
    // Now we have both keypoints and descriptors for this frame. {kps, descriptors}

    // do some matching and then return kps and des 
    // [DONE] and draw them on the frame 
    if (!prev_.desc.empty())
    {
     // do the matching here.  
    }
    
    prev_.kps = keypoints;
    prev_.desc = descriptors; 

    return keypoints;
  }
 private:
  cv::Ptr<cv::DescriptorExtractor> detector_ = cv::ORB::create();
  struct kpDesc prev_;
};