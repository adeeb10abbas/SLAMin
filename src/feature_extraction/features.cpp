
#include "opencv2/opencv_modules.hpp"

using namespace cv;

class FeatureProcessing{
 public:
    FeatureProcessing(vector<KeyPoint>* kp){        
    }
    virtual void ProcessImage(){
    }
 private:
    int minHessian_ = 400;
}