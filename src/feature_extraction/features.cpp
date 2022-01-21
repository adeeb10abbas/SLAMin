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

// inline void featureProcessing::processImage(Mat& image1){
//     std::vector<KeyPoint>& kp;
//     cv::OutPutArray dp;
//     Feature2D::detectAndCompute(image1, kp, dp);
//     cout << kp;
// }