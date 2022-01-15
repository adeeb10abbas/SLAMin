#include "opencv2/opencv.hpp"
#include "iostream"
#include "display.hpp"
using namespace cv;
using namespace std;

int main(int, char**) {
    VideoCapture cap("videos/test_nyc.mp4");
    if ( !cap.isOpened() )  // isOpened() returns true if capturing has been initialized.
    {
        cout << "Cannot open the video file. \n";
        return -1;
    }

    double fps = cap.get(CAP_PROP_FPS); //get the frames per seconds of the video

    namedWindow("slam",WINDOW_NORMAL); 
    while(1)
    {
        Mat frame;
        // Mat object is a basic image container. frame is an object of Mat.
        if (!cap.read(frame)) 
        // if not success, break loop
        // read() decodes and captures the next frame.
        {
            cout<<"\n Cannot read the video file. \n";
            break;
        }
        // cout << frame.<< endl << "\n";
        return 0;
        // Take out each dimension like this - vector<Mat> md(92,Mat(112,200,CV_32F));
        // imshow("A_good_name", frame);
        // first argument: name of the window.
        // second argument: image to be shown(Mat object).

        if(waitKey(30) == 27) // Wait for 'esc' key press to exit
        { 
            break; 
        }
    }
    return 0;
}

// #include <SFML/Graphics.hpp>

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         window.draw(shape);
//         window.display();
//     }

//     return 0;
// }