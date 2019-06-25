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

using namespace std;
using namespace cv;

//https://www.lucidar.me/en/dev-c-cpp/reading-xml-files-with-qt/
//http://doc.crossplatform.ru/qt/4.7.x/qstring.html



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



    // ===LOAD_AND_READ_FROM_XML===
    QFile f("/testdata/tor/out/tor.028/tor.028.021.left.avi.dat/test.xml");
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        cerr << "Error while loading file" << endl;
        return 1;
    }

    if (xmlBOM.setContent(&f))
    {
        cout << "Set is contained" << endl;
    }
    else
    {
        cout << "Bad XML from BOM" << endl;
    }
    f.close();

    // ===DATA_ACCESS===
    QDomElement root = xmlBOM.documentElement();
    QDomElement Component=root.firstChild().toElement();


    while(!Component.isNull())
    {
        cout << "1 check PASS" << endl;
        // Check if the child tag name is COMPONENT
        if (Component.tagName()=="FrameDataArray")
        {
            cout << "2 check PASS" << endl;
            // Read and display the component ID
            //QString ID=Component.attribute("ID","No ID");

            // Get the first child of the component
            QDomElement Child=Component.firstChild().toElement();

            QString Name;
            int Q1;
            double Value;
            int n = 0; // Counter for <_>

            // Read each child of the component node
            while (!Child.isNull())
            {
                n++;
                cout << "3 check PASS " << n << endl;

                // Read Name and value
                if (Child.tagName()=="_") // Into the <_>
                {
                    cout << "in the <_Circle>" << endl;
                    //Name=Child.firstChild().toText().data();

                    QDomElement Child1=Child.firstChild().toElement();
                                if (Child1.tagName()=="FrameNumber")
                                    {
                                        cout << "printed 1 FrameNumber" << endl;
                                        Child1 = Child1.nextSibling().toElement();
                                    }
                                if (Child1.tagName()=="FrameObjects")
                                    {
                                        cout << "printed 1 FrameObjects" << endl;
                                    }

                    while(!Child1.isNull())
                        {
                                    if (Child1.tagName()=="FrameObjects")
                                        {
                                            cout << "printed 2 FrameObjects" << endl;
                                        }
                                        //cout << "in the <_>" << endl;
                                    if (Child1.tagName()=="FrameObjects") // Into the <FrameObjects>
                                        {
                                            cout << "in the <FrameObjects>" << endl;
                                            QDomElement Child2=Child1.firstChild().toElement(); // <_>

                                            if (Child2.tagName()=="_")
                                                {
                                                    cout << "PASS" << endl;
                                                    QDomElement Child3=Child2.firstChild().toElement();
                                                    Child3 = Child3.nextSibling().toElement();
                                                    if (Child3.tagName()=="rect")
                                                    {
                                                        cout << "Dekita yo!" << endl;

                                                        Name = Child3.firstChild().toText().data();


                                                        cout << " xxx= " << Name.toStdString().c_str() << endl;
                                                    }
                                                }
                                        }
                                    Child1 = Child1.nextSibling().toElement();
                        }
                }

                // Next child
                Child = Child.nextSibling().toElement();
            }

            // Display component data
           // std::cout << "Component " << ID.toStdString().c_str() << std::endl;
            std::cout << "   Name  = " << Name.toStdString().c_str() << std::endl;
            std::cout << "   Value Q1 = " << Q1 << std::endl;
            std::cout << std::endl;
        }

        // Next component
        Component = Component.nextSibling().toElement();
    }








    //===WORK_WITH_IMAGE===
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
