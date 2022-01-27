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
#include "opencv2/xfeatures2d.hpp"
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/ocl.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

struct kpDesc {
  std::vector<cv::KeyPoint> kps;
  Mat desc;
};

class featureProcessing{
 public:
   std::vector<cv::KeyPoint> processImage(Mat& image);
   Mat calculateCamMat (const Mat& image, std::vector<cv::KeyPoint>& points1,
                    std::vector<cv::KeyPoint>& points2);
 private:
  // cv::Ptr<cv::DescriptorExtractor> detector_ = cv::ORB::create();
  // cv::Ptr<cv::FeatureDetector> detector_ = new cv::SurfFeatureDetector();
  Ptr<SURF> detector_=SURF::create();

  struct kpDesc prev_;
  cv::BFMatcher matcher_;
};