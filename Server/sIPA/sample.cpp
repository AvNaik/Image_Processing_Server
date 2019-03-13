#include <opencv2/opencv.hpp>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace cv;

int main( int argc, char** argv )
{

	char *ipImage = strtok(argv[1], "#");
	char *opImage = strtok(NULL, "#");
	char *oper = strtok(NULL, "#");
	/*cout << ipImage << endl;
	cout << opImage << endl;
	cout << oper << endl;*/

	//char* ipImage = argv[1];

	Mat image;
	image = imread( ipImage, 1 );

	if( argc != 2 || !image.data )
	{
		printf( " No image data [%d]\n ", argc);
		return -1;
	}

	Mat gray_image;
	cvtColor( image, gray_image, COLOR_BGR2GRAY );
	
	imwrite( opImage, gray_image );

	/*namedWindow( ipImage, WINDOW_AUTOSIZE );
	namedWindow( "Gray image", WINDOW_AUTOSIZE );
	
	imshow( ipImage, image );
	imshow( "Gray image", gray_image );
	
	waitKey(0);*/
	
	return 0;
}
