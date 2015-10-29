#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  Mat src, src_gray, dst_canny, dst_int, dst_eq;

  src = imread( argv[1], 1 );

  if( !src.data )
    { cout<<"Usage: <path_to_image>"<<endl;
      return -1;}

  namedWindow( "Source image", CV_WINDOW_AUTOSIZE );
  imshow( "Source image", src );


  Canny(src, dst_canny, 50, 100, 3);
  namedWindow( "Canny image", CV_WINDOW_AUTOSIZE );
  imshow( "Canny image", dst_canny );

  cvtColor(src, src_gray, COLOR_BGR2GRAY);
  equalizeHist(src_gray, dst_eq);
  namedWindow( "EqualizeHist image", CV_WINDOW_AUTOSIZE );
  imshow( "EqualizeHist image", dst_eq );
 


  integral(src, dst_int);
  namedWindow( "Integral image", CV_WINDOW_AUTOSIZE );

  imshow( "Integral image", dst_int );

  waitKey(0);

  return 0;
}

