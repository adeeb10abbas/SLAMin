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
    cv::goodFeaturesToTrack(image,corners, 500, 0.01, 10);
    return corners;
  }
//  private:
  //  Ptr<Feature2D> detector = SIFT::create(800.0);
};