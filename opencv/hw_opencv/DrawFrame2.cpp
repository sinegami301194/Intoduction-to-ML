#include <QCoreApplication>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
//#include <ocvgui.h>
//#include <ar10/ocvgui.h>
//#include <arcore/markup_reader.h>
//#include <framedata/framedata.h>

#include <string>
#include <iostream>

using namespace cv;
using namespace std;

class FrameObjectsContain
{
public:
    FrameObjectsContain() : x(0), y(0), w(0), h(0), flags(0), index(0), zOrder(0),
                            occlusionRate(0.0), track(0), tag()
    {}
    explicit FrameObjectsContain(int) : x(394), y(114), w(92), h(76),
                                        flags(16), index(0), zOrder(0), occlusionRate(0.),
                                        track(-1), tag("Rear") // explicit to avoid implicit conversion
    {}
    void read(const FileNode& node)                          //Read serialization for this class
    {
        type = (string)node["type"];
        flags = (int)node["flags"];
        index = (int)node["index"];
        zOrder = (int)node["zOrder"];
        occlusionRate = (double)node["occlusionRate"];
        track = (int)node["track"];
        tag = (string)node["tag"];
        if (node["rect"].isSeq() && node["rect"].size() == 4)
        {
          node >> x;
          node >> y;
          node >> w;
          node >> h;
        }
    }
public:   // Data Members
    string type;
    int x;
    int y;
    int w;
    int h;
    int flags;
    int index;
    int zOrder;
    double occlusionRate;
    int track;
    string tag;
};

class MyData
{
public:
    MyData() : A(0), X(0), id()
    {}
    explicit MyData(int) : A(97), X(CV_PI), id("mydata1234") // explicit to avoid implicit conversion
    {}
    void read(const FileNode& node)                          //Read serialization for this class
    {
        A = (int)node["A"];
        X = (double)node["X"];
        id = (string)node["id"];
    }
public:   // Data Members
    int A;
    double X;
    string id;
};

static void read(const FileNode& node, MyData& x, const MyData& default_value = MyData()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

// This function will print our custom class to the console
static ostream& operator<<(ostream& out, const MyData& m)
{
    out << "{ id = " << m.id << ", ";
    out << "X = " << m.X << ", ";
    out << "A = " << m.A << "}";
    return out;
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    string filename = "/testdata/tor/out/tor.028/tor.028.021.left.avi.dat/tor.028.021.left.avi.frameData.xml";
    {//read
        cout << endl << "Reading: " << endl;
        FileStorage fs;
        fs.open(filename, FileStorage::READ);

        int itNr;
        //fs["iterationNr"] >> itNr;
        itNr = (int) fs["iterationNr"];
        cout << itNr;
        if (!fs.isOpened())
        {
            cerr << "Failed to open " << filename << endl;
            return 1;
        }

        FileNode FDA = fs["FrameDataArray"];                         // Read string sequence - Get node
        cout << FDA.type() << FDA.name() << "PASS" << endl;
        if (FDA.type() != FileNode::SEQ)
        {
            cerr << "strings is not a sequence! FAIL" << endl;
            return 1;
        }

        FileNodeIterator itFDA = FDA.begin(), it_end = FDA.end();                           // Go through the node FrameDataArray
        for (; itFDA != it_end; ++itFDA)
        {
            FileNode underscore_1 = *itFDA;
            FileNodeIterator itUS1 = underscore_1.begin(), itUS1_end = underscore_1.end();  // Go through the node underscore_1
            for (; itUS1 != itUS1_end; ++itUS1)
            {
                int FrameNumber = (int)(underscore_1["FrameNumber"]);
                cout << FrameNumber << endl;
                FileNode FrameObjects = underscore_1["FrameObjects"];                        // Go through the node FrameObjects
                FileNodeIterator itFO = FrameObjects.begin(), in_end = FrameObjects.end();  // Go through the node underscore_2
                FileNode US2 = *itFO;

                string type = (string)(US2["type"]);
                int flags = (int)(US2["flags"]);

                cout << type << endl;
                cout << flags << endl;

            }
        }

        FDA = fs["Mapping"];                                // Read mappings from a sequence
        cout << "Two  " << (int)(FDA["Two"]) << "; ";
        cout << "One  " << (int)(FDA["One"]) << endl << endl;


        MyData m;
        Mat R, T;

        fs["R"] >> R;                                      // Read cv::Mat
        fs["T"] >> T;
        fs["MyData"] >> m;                                 // Read your own structure_

        cout << endl
            << "R = " << R << endl;
        cout << "T = " << T << endl << endl;
        cout << "MyData = " << endl << m << endl << endl;

        //Show default behavior for non existing nodes
        cout << "Attempt to read NonExisting (should initialize the data structure with its default).";
        fs["NonExisting"] >> m;
        cout << endl << "NonExisting = " << endl << m << endl;
        }
}

/*bool load_from_XML(QDomDocument& xmlBOM, const char* XML_PATH)
{
    QFile f(XML_PATH); // Load XML from path
    if (!f.open(QIODevice::ReadOnly))
    {
        // Error while loading file
        cerr << "Error while loading file" << endl;
        return false;
    }
    xmlBOM.setContent(&f);
    f.close();
    return true;
}

bool parsing_rect_params(string f, int& x, int& y, int& w, int& h)
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
    x = stoi(result[0]); y = stoi(result[1]);
    w = stoi(result[2]); h = stoi(result[3]);
    return 0;
}

bool draw_text_rect(Mat& frame, const char * str, int x, int y, int w, int h)
{
    putText(frame, str, cvPoint(30,30),
           FONT_HERSHEY_COMPLEX_SMALL, 1.0, cvScalar(128,255,255), 1, CV_AA);
    rectangle(frame,Rect(x, y, w, h), Scalar(128,255,255),2);
    return true;
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    // ===PATH_VARIABLES_DECLARATION_AND_DEFINITION===
    const String &Video_PATH = "/testdata/tor/inp/tor.028/tor.028.021.left.avi";
    const char* XML_PATH = "/testdata/tor/out/tor.028/tor.028.021.left.avi.dat/tor.028.021.left.avi.frameData.xml";

    // ===OTHER_VARIABLES_DECLARATION===
    int x, y, w, h;
    QDomDocument xmlBOM;
    QString Name;
    VideoCapture cap(Video_PATH);

    // ===PREPEARING_FOR_WRITING_VIDEO===
    int frame_number = 0;
    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    VideoWriter video("/home/alpatikov_i/Pictures/test.avi",CV_FOURCC('M','J','P','G'),
                      10, Size(frame_width,frame_height),true);

    // ===LOAD_AND_READ_FROM_XML===
    load_from_XML(xmlBOM, XML_PATH);

    // ===DATA_ACCESS===
    QDomElement root = xmlBOM.documentElement();
    QDomElement Component=root.firstChild().toElement(); // Set Component as "FrameDataArray"
    while(!Component.isNull()) // Start reading in the "FrameDataArray"
    {
            // Get the first child of the component
            QDomElement Child=Component.firstChild().toElement(); // Get first <_>
            while (!Child.isNull()) // Read each child of the component node
            {
                   QDomElement Child1=Child.firstChild().toElement(); // Get <_>'s first child
                   Child1 = Child1.nextSibling().toElement(); // Go to next <_>'s child ("FrameObjects")
                   while(!Child1.isNull()) // In the "FrameObjects" start circle
                   {
                        QDomElement Child2=Child1.firstChild().toElement(); // Get second <_>
                        QDomElement Child3=Child2.firstChild().toElement(); // Get first <_>'s child ("type")
                        Child3 = Child3.nextSibling().toElement(); // Go to next <_>'s child ("rect")
                        Name = Child3.firstChild().toText().data(); // Variable defenition
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

                        Child1 = Child1.nextSibling().toElement(); // Next child
                    }
                Child = Child.nextSibling().toElement(); // Next child
                frame_number++;
            }
        Component = Component.nextSibling().toElement(); // Next component
    }
    destroyAllWindows();
    return 0;
}
*/
