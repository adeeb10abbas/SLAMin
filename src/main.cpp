#include "opencv2/opencv.hpp"
#include "iostream"
#include "feature_extraction/features.hpp"

using namespace cv;
using namespace std;

int main(int argc,char* argv[]){
  
  VideoCapture cap(argv[1]); 
   
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
    if (frame.empty())
      break;
    auto adeeb = fp.processImage(frame);
    cout << adeeb[0];
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