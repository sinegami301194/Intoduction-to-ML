#include <QCoreApplication>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
//#include <ocvgui.h>
#include <ar10/ocvgui.h>
#include <arcore/markup_reader.h>
#include <framedata/framedata.h>
#include <QtXml>
#include <QFile>

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace cv;

// Usefull links:
//https://www.lucidar.me/en/dev-c-cpp/reading-xml-files-with-qt/
//http://doc.crossplatform.ru/qt/4.7.x/qstring.html

bool parsing_rect_params(string f, int x, int y, int w, int h)
{
    string s;
    vector<string> result;
    boost::split(result, f, boost::is_any_of(" "));
    int rect_param_count = 0;
    for (int i = 0; i < result.size(); i++)
    {
        if ((result[i] != "\n") && (result[i] != " ") && (result[i] != ""))
        {
            result[rect_param_count] = result[i];
            rect_param_count++;
        }
    }
    x = stoi(result[0]);
    y = stoi(result[1]);
    w = stoi(result[2]);
    h = stoi(result[3]);
    return 0;
}

bool draw_text_rect(Mat frame, const char * str, int x, int y, int w, int h)
{
    putText(frame, str, cvPoint(30,30),
           FONT_HERSHEY_COMPLEX_SMALL, 1.0, cvScalar(128,255,255), 1, CV_AA);
    rectangle(frame,Rect(x, y, w, h), Scalar(128,255,255),2);
    return 0;
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    // ===PATH_VARIABLES_DECLARATION_AND_DEFINITION===
    string Image_PATH = "/home/alpatikov_i/Pictures/p2.jpg";
    const String &Video_PATH = "/testdata/tor/inp/tor.028/tor.028.021.left.avi";
    const char* XML_PATH = "/testdata/tor/out/tor.028/tor.028.021.left.avi.dat/tor.028.021.left.avi.frameData.xml";
    QString XML_P = "/testdata/tor/out/tor.028/tor.028.021.left.avi.dat/test.xml";

    // ===OTHER_VARIABLES_DECLARATION===
    string Text_info;
    QDomDocument xmlBOM;
    int x, y, w, h;

    VideoCapture cap(Video_PATH);

    int frame_number = 0;
    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    VideoWriter video("/home/alpatikov_i/Pictures/test.avi",CV_FOURCC('M','J','P','G'),
                                                10, Size(frame_width,frame_height),true);

    // ===LOAD_AND_READ_FROM_XML===
    QFile f("/testdata/tor/out/tor.028/tor.028.021.left.avi.dat/test.xml"); // Load XML from path
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        cerr << "Error while loading file" << endl;
        return 1;
    }

    if (xmlBOM.setContent(&f)) // Fill the data from XML
    {
        cout << "Set is contained" << endl;
    }
    f.close();

    // ===DATA_ACCESS===
    QDomElement root = xmlBOM.documentElement();
    QDomElement Component=root.firstChild().toElement(); // Set Component as "FrameDataArray"

    while(!Component.isNull()) // Start reading in the "FrameDataArray"
    {
        // Check if the child tag name is COMPONENT
        if (Component.tagName()=="FrameDataArray")
        {
            // Get the first child of the component
            QDomElement Child=Component.firstChild().toElement(); // Get first <_>

            // ===VARIABLE_DECLARATION===
            QString Name;

            // Read each child of the component node
            while (!Child.isNull())
            {
                if (Child.tagName()=="_") // Into the <_>
                {
                   QDomElement Child1=Child.firstChild().toElement(); // Get <_>'s first child
                    if (Child1.tagName()=="FrameNumber") // Go to next <_>'s child ("FrameObjects")
                    {
                        Child1 = Child1.nextSibling().toElement();
                    }
                    while(!Child1.isNull()) // In the "FrameObjects" start circle
                    {
                        if (Child1.tagName()=="FrameObjects") // Into the <FrameObjects>
                        {
                            QDomElement Child2=Child1.firstChild().toElement(); // Get second <_>

                            if (Child2.tagName()=="_") // Into the second <_>
                            {
                                QDomElement Child3=Child2.firstChild().toElement(); // Get first <_>'s child ("type")
                                Child3 = Child3.nextSibling().toElement(); // Go to next <_>'s child ("rect")
                                if (Child3.tagName()=="rect") // Into the <rect>
                                {
                                    Name = Child3.firstChild().toText().data(); // Variable defenition
                                    cout << " xxx= " << Name.toStdString().c_str() << endl; // Testing write
                                    {
                                        string f(Name.toStdString());
                                        
                                        //===PARSING_RECTANGLE_PARAMETRS_STRING===
                                        parsing_rect_params(f, x, y, w, h);

                                        // ===DRAW_RECTANGLES===SHOW_PICTURES==WRITE_VIDEO_OUTPUT===
                                        Mat frame;
                                        cap >> frame;
                                        string frame_str = string("Frame number: ").append(to_string(frame_number));
                                        const char * str = frame_str.c_str();
                                        draw_text_rect(frame, str, x, y, w, h);
                                        namedWindow("win",WINDOW_AUTOSIZE);
                                        imshow("win",frame);
                                        video.write(frame);
                                        char c = (char)waitKey(33);
                                        if( c == 27 ) break;
                                    }
                                }
                            }
                        }
                    Child1 = Child1.nextSibling().toElement();
                    }
                }
                // Next child
                Child = Child.nextSibling().toElement();
                frame_number++;
            }
            // Display component data
            std::cout << "   Name  = " << Name.toStdString().c_str() << std::endl;
            std::cout << std::endl;
        }
        // Next component
        Component = Component.nextSibling().toElement();
    }

    //===WORK_WITH_IMAGE===
    destroyAllWindows();
    return 0;
}
