/*!\file window.cpp
 *
 * \brief Utilisation du CascadeClassifier pour détecter des visages
 *
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date October 15 2015
 */
#include <stdio.h>
#include <assert.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;
using namespace std;

// Variables globales

int main(int argc, char ** argv) {
  CascadeClassifier * face_cc = NULL;
  VideoCapture * cap = new VideoCapture(0);
  face_cc = new CascadeClassifier("haarcascade_frontalface_default.xml");
  if(!cap->isOpened()) {
    delete cap;
    cap = new VideoCapture(CV_CAP_ANY);
  }
  if(face_cc == NULL || !cap->isOpened()) {
    if(face_cc) delete face_cc;
    if(cap) delete cap;
    return 1;
  }
  cap->set(CV_CAP_PROP_FRAME_WIDTH,  500);
  cap->set(CV_CAP_PROP_FRAME_HEIGHT, 500);
  Mat ci, gsi;

  cv::Mat image = cv::imread("mignonSmile.png",cv::IMREAD_UNCHANGED);


  namedWindow("Face detection", WINDOW_NORMAL);
  while(1) {
    *cap >> ci;
    vector<Rect> faces;
    cvtColor(ci, gsi, COLOR_BGR2GRAY);
    face_cc->detectMultiScale(gsi, faces, 1.3, 5);
    for (vector<Rect>::iterator fc = faces.begin(); fc != faces.end(); ++fc) {
      
       if(image.data )         
      {
        cv::imshow( "Face detection", image ); 
        cv::waitKey(0);
      }else{
        rectangle(ci, (*fc).tl(), (*fc).br(), Scalar(0, 255, 0), 2, CV_AA);
      }


    }
    imshow("Face detection", ci);
    if((waitKey(10) & 0xFF) == 27)
      break;
  }
  return 0;
}
