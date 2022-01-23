#include "opencv2/opencv.hpp"
#include "iostream"
#include "feature_extraction/features.hpp"

using namespace cv;
using namespace std;
#define radius 3

int main(int argc,char* argv[]){
  
  VideoCapture cap("videos/test_countryroad.mp4");
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
	featureProcessing fp;
  while(1){

    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
    // If the frame is empty, break immediately
    Mat grayscale;
    cvtColor(frame, grayscale, COLOR_BGR2GRAY);

    if (frame.empty())
      break;

    vector<cv::Point2f> corners = fp.processImage(grayscale);
    #pragma omp for
    for (size_t i = 0; i < corners.size(); i++)
    {
      cv::circle(frame, corners.at(i), radius, cv::Scalar (255, 0, 0), FILLED);
    }
    
    // Display the resulting frame
    imshow("Frame", frame);

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}