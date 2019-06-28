#include <QCoreApplication>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <string>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

class FrameObjectsContain
{
public:
  FrameObjectsContain() : x(0), y(0), w(0), h(0), flags(0), index(0), zOrder(0),
    occlusionRate(0.0), track(0), tag()
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
      std::vector<int> zz;
      node["rect"] >> zz;
      x = zz[0];
      y = zz[1];
      w = zz[2];
      h = zz[3];
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

  const String &Video_PATH = "/testdata/tor/inp/tor.028/tor.028.021.left.avi";
  VideoCapture cap(Video_PATH);

  // ===PREPEARING_FOR_WRITING_VIDEO===
  int frame_number = 0;
  int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  VideoWriter video("/home/alpatikov_i/Pictures/DrawFrameData.avi",CV_FOURCC('M','J','P','G'),
                    10, Size(frame_width,frame_height),true);

  string filename = "/testdata/tor/out/tor.028/tor.028.021.left.avi.dat/tor.028.021.left.avi.frameData.xml";
  {
    //read
    FileStorage fs;
    fs.open(filename, FileStorage::READ);
    int itNr;
    itNr = (int) fs["iterationNr"];
    if (!fs.isOpened())
    {
      cerr << "Failed to open " << filename << endl;
      return 1;
    }
    FileNode FDA = fs["FrameDataArray"];                                                 // Read string sequence - Get node
    if (FDA.type() != FileNode::SEQ)
    {
      cerr << "strings is not a sequence! FAIL" << endl;
      return 1;
    }
    FileNodeIterator itFDA = FDA.begin(), it_end = FDA.end();                            // Go through the node FrameDataArray
    for (; itFDA != it_end; ++itFDA)
    {
      FileNode underscore_1 = *itFDA;
      FileNodeIterator itUS1 = underscore_1.begin(), itUS1_end = underscore_1.end();   // Go through the node underscore_1

      int FrameNumber = (int)(underscore_1["FrameNumber"]);
      FileNode FrameObjects = underscore_1["FrameObjects"];
      FileNodeIterator itFO = FrameObjects.begin();                                // Go through the node FrameObjects
      FileNode US2 = *itFO;                                                        // Go through the node underscore_2
      FrameObjectsContain node;
      node.read(US2);

      // ===DRAW_RECTANGLES===SHOW_PICTURES==WRITE_VIDEO_OUTPUT===
      Mat frame;
      cap >> frame;
      string frame_str = string("Frame number: ").append(to_string(FrameNumber));
      const char * str = frame_str.c_str();
      draw_text_rect(frame, str, node.x, node.y, node.w, node.h);
      namedWindow("win",WINDOW_AUTOSIZE);
      imshow("win",frame);
      video.write(frame);
      char c = (char)waitKey(33);
      if( c == 27 ) break;
    }
  }
  destroyAllWindows();
  return 0;
}
