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

using namespace cv;
using namespace std;

class featureProcessing{
 public:
   featureProcessing(){}
   std::vector<cv::Point2f> processImage(Mat& image) {
    std::vector<cv::Point2f> corners;
    vector<float> descriptors;
    cv::goodFeaturesToTrack(image, corners, 3000, 0.01, 4);
    // Generate ORBs from keypoints
    std::vector<cv::KeyPoint> kp;
    #pragma omp for
    for (size_t i = 0; i < corners.size() ; i++)
    {
      kp.emplace_back(KeyPoint(corners.at(i), 20));
    }
    detector->compute(image, kp, descriptors);
    // the computation was the issue we'll figure this out later. 
    return corners;
  }
 private:
  cv::Ptr<cv::DescriptorExtractor> detector = cv::ORB::create();
};