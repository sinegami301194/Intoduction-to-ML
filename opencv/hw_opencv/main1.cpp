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

bool load_from_XML(const char* word, QDomDocument xmlBOM)
{
    //The QDomDocument class represents an XML document.
    //QDomDocument xmlBOM;
    // Load xml file as raw data
    QFile f(word);
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        cerr << "Error while loading file" << endl;
        return 1;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f);
    f.close();
    return true;
}

bool read_from_XML(QDomDocument &xmlBOM, QDomElement &root)
{
    // Extract the root markup
    root = xmlBOM.documentElement();

    // Get root names and attributes
    QString Type=root.tagName();
    QString Board=root.attribute("BOARD","No name");
    int Year=root.attribute("YEAR","1900").toInt();

    // Display root data
    cout << "Type  = " << Type.toStdString().c_str() << endl;
    cout << "Board = " << Board.toStdString().c_str() << endl;
    cout << "Year  = " << Year << endl;
    cout << endl;
    return true;
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    // ===PATH_VARIABLES_DECLARATION_AND_DEFINITION===
    string Image_PATH = "/home/alpatikov_i/Pictures/p2.jpg";
    const String& Video_PATH = "/testdata/tor/inp/tor.028/tor.028.021.left.avi";
    const char* XML_PATH = "/testdata/tor/out/tor.028/tor.028.021.left.avi.dat/tor.028.021.left.avi.frameData.xml";

    // ===OTHER_VARIABLES_DECLARATION===
    string Text_info;
    QDomDocument xmlBOM;
    QDomElement root;

    // ===LOAD_AND_READ_FROM_XML===
    load_from_XML(XML_PATH, xmlBOM);
    read_from_XML(xmlBOM, root); // Reading first node

    // ===DATA_ACCESS===
    // Get the first child of the root (Markup COMPONENT is expected)

    QDomElement Component=root.firstChild().toElement();


    // Loop while there is a child
    while(!Component.isNull())
    {
        // Check if the child tag name is COMPONENT
        if (Component.tagName()=="COMPONENT")
        {

            // Read and display the component ID
            QString ID=Component.attribute("ID","No ID");

            // Get the first child of the component
            QDomElement Child=Component.firstChild().toElement();

            QString Name;
            double Value;

            // Read each child of the component node
            while (!Child.isNull())
            {
                // Read Name and value
                if (Child.tagName()=="NAME") Name=Child.firstChild().toText().data();
                if (Child.tagName()=="VALUE") Value=Child.firstChild().toText().data().toDouble();

                // Next child
                Child = Child.nextSibling().toElement();
            }

            // Display component data
            std::cout << "Component " << ID.toStdString().c_str() << std::endl;
            std::cout << "   Name  = " << Name.toStdString().c_str() << std::endl;
            std::cout << "   Value = " << Value << std::endl;
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
