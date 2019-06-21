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
    Mat img = imread(Image_PATH, IMREAD_COLOR);

    rectangle(img,Rect(210,80,50,40), Scalar(255,128,128),2);
    putText(img, "Differencing the two images.", cvPoint(30,30),
            FONT_HERSHEY_COMPLEX_SMALL, 1.0, cvScalar(255,1,128), 1, CV_AA);
    
    namedWindow("win",WINDOW_AUTOSIZE);
    imshow("win",img);
    waitKey(0);
    return 1;

    return 0;
}
