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
   std::pair processImage(Mat& image1) {
      detector->detectAndCompute(image1, Mat(), kp, dp);
      cout << 0;
      cout << (float)dp.at<float>(0,0);
      return std::make_pair(kp, dp);
    }
 private:
   Ptr<Feature2D> detector = SIFT::create(800.0);
   cv::Mat dp;
   vector<KeyPoint> kp;
};