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

    namedWindow("win",WINDOW_AUTOSIZE);
    imshow("win",img);
    waitKey(0);
    return 1;

    return 0;
}
