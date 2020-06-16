/*
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;



int main()
{
	Mat img_color = imread("ImgTest1616.jpg", IMREAD_COLOR);


	int height = img_color.rows;
	int width = img_color.cols;


	uchar *data = img_color.data;

	for (int y = 0; y < height; y++) {
		printf("\n");
		for (int x = 0; x < width; x++) {

			int b = data[y * width * 3 + x * 3];
			printf("%3d ",b);
			
			}
		}
		
	return 0;
}
*/