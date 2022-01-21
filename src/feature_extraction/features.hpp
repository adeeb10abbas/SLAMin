#include "opencv2/opencv_modules.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;
class FeatureProcessing{
 public:
    FeatureProcessing(){}
    virtual void ProcessImage(Mat& image1){}
 private:
    int minHessian_ = 400;
    vector<KeyPoint> kp_;
    SiftFeatureDetector detector_;
};