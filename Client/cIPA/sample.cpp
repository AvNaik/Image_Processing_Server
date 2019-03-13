#include <opencv2/opencv.hpp>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace cv;

int main( int argc, char** argv )
{

	char *ipImage = strtok(argv[1], "#");
	char *opImage = strtok(NULL, "#");

	Mat ipImImage;
	Mat opImImage;

	ipImImage = imread( ipImage, 1 );
	opImImage = imread( opImage, 1 );

	if( !ipImImage.data )
	{
		printf( " No input image [%s] data [argc=%d]\n ", ipImage, argc);
		return -1;
	}

	if( !opImImage.data )
	{
		printf( " No input image [%s] data [argc=%d]\n ", opImage, argc);
		return -1;
	}

	 namedWindow( ipImage, WINDOW_AUTOSIZE );
	 namedWindow( opImage, WINDOW_AUTOSIZE );
	 imshow( ipImage, ipImImage);
	 waitKey(3000);
	 imshow( opImage, opImImage);

	 waitKey(7000);
	 destroyAllWindows();

	return 0;
}
