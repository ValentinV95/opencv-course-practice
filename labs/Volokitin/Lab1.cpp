#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  Mat src, dst_canny, dst_conter, dst_transform, dst_int, output;

  Mat bgr[3];
  Mat out_bgr[3];

  src = imread( argv[1], 1 );

  if( !src.data )
    { cout<<"Usage: <path_to_image>"<<endl;
      return -1;}

  namedWindow( "Source image", CV_WINDOW_AUTOSIZE );
  imshow( "Source image", src );

  Canny(src, dst_canny, 50, 100, 3);

  dst_conter=~dst_canny;
  dst_transform=src.clone();

  distanceTransform(dst_conter, dst_transform, CV_DIST_L2, 3);

  split(src, bgr);

  for (int i=0; i<3; i++)
  {
	out_bgr[i]=bgr[i].clone();
  }

  int minx, miny, maxx, maxy;
  double div;
  float r;
  for(int i=0; i<3; i++)
  {
    integral(bgr[i], dst_int);
	for(int j=0; j<out_bgr[i].rows; j++)
	{
		for(int k=0; k<out_bgr[i].cols; k++)
		{
			int blur;
			r=dst_transform.at<float>(j, k);
			int kernel=r/2;
			minx=0; maxx=out_bgr[i].rows-1;
			if(j-kernel>-1)
				minx=j-kernel;
			if(j+kernel<out_bgr[i].rows)
				maxx=j+kernel;

			miny=0; maxy=out_bgr[i].cols-1;
			if(k-kernel>-1)
				miny=k-kernel;
			if(k+kernel<out_bgr[i].cols)
				maxy=k+kernel;
			div=1./(maxx-minx+1)/(maxy-miny+1);
			if(kernel>0)
			{
				blur=((dst_int.at<int>(minx,miny)
					-dst_int.at<int>(maxx+1,miny)
					-dst_int.at<int>(minx,maxy+1)
					+dst_int.at<int>(maxx+1,maxy+1))*div);
			}
			else
			{
				blur=bgr[i].at<unsigned char>(j,k);
			}
			out_bgr[i].at<unsigned char>(j,k)=(unsigned char) blur;
		}
	}
  }

  merge(out_bgr, 3, output);
  namedWindow( "Output image", CV_WINDOW_AUTOSIZE );

  imshow( "Output image", output );

  waitKey(0);

  return 0;
}

