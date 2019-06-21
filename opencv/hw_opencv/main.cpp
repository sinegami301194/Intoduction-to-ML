#include <QCoreApplication>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
//#include <ar10/ocvgui.h> // for argui::imshow and etc.

#include <string>
#include <iostream>

using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    string Image_PATH = "/home/alpatikov_i/Pictures/p2.jpg";
    string Text_info;
    const String& Video_PATH = "/testdata/tor/inp/tor.028/tor.028.021.left.avi";

    //Mat img = imread(Image_PATH, IMREAD_COLOR);
    Mat frame;
    VideoCapture cap(Video_PATH);
    cap >> frame;
    putText(frame, "Frame number: 0", cvPoint(30,30),
           FONT_HERSHEY_COMPLEX_SMALL, 1.0, cvScalar(128,255,255), 1, CV_AA);
    //rectangle(img,Rect(394, 114, 92, 76), Scalar(255,128,128),2);

    rectangle(frame,Rect(394, 114, 92, 76), Scalar(128,255,255),2);

    namedWindow("win",WINDOW_AUTOSIZE);
    //imshow("win",img);
    imshow("win",frame);
    imwrite("/home/alpatikov_i/Pictures/p5.jpg", frame);
    waitKey(0);
    destroyAllWindows();

    return 0;
}
