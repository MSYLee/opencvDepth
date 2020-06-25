
#include <opencv2/opencv.hpp>
#include <iostream>

#include <stdio.h>
#include <string>
#include <time.h>

#include "serialcomm.h"




using namespace cv;
using namespace std;
int pixel;
int color;
int colortmp;

int matArr_1[16][16] = {
  {49, 49, 49, 49, 49, 49, 49, 53, 53, 49, 49, 49, 49, 49, 49, 49},
  {49, 49, 49, 49, 49, 49, 53, 50, 50, 53, 49, 49, 49, 49, 49, 49},
  {49, 49, 49, 49, 49, 49, 53, 50, 50, 53, 49, 49, 49, 49, 49, 49},
  {49, 49, 49, 49, 49, 53, 50, 50, 50, 50, 53, 49, 49, 49, 49, 49},
  {53, 53, 53, 53, 53, 53, 50, 50, 50, 50, 53, 53, 53, 53, 53, 53},
  {53, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 53},
  {53, 53, 50, 50, 50, 53, 53, 50, 50, 53, 53, 50, 50, 50, 53, 53},
  {49, 49, 53, 50, 50, 53, 53, 50, 50, 53, 53, 50, 50, 53, 49, 49},
  {49, 49, 49, 53, 50, 53, 53, 50, 50, 53, 53, 50, 53, 49, 49, 49},
  {49, 49, 49, 53, 50, 53, 53, 50, 50, 53, 53, 50, 53, 49, 49, 49},
  {49, 49, 53, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 53, 49, 49},
  {49, 49, 53, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 53, 49, 49},
  {49, 53, 50, 50, 50, 50, 50, 53, 53, 50, 50, 50, 50, 50, 53, 49},
  {53, 53, 50, 50, 50, 53, 53, 49, 49, 53, 53, 50, 50, 50, 53, 53},
  {53, 50, 50, 53, 53, 49, 49, 49, 49, 49, 49, 53, 53, 50, 50, 53},
  {53, 53, 53, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 53, 53, 53}
};
int matArr_2[16][16];

int tmpArr[16][16];

//VideoCapture cap(0);


void connSeria() {


}

void delay(clock_t n)

{

	clock_t start = clock();

	while (clock() - start < n);

}

void detColor() {

	if (colortmp < 51) {
		color = 49;
	}
	else if (colortmp < 102 && colortmp > 50) {
		color = 50;
	}
	else if (colortmp < 153 && colortmp > 101) {
		color = 51;
	}
	else if (colortmp < 204 && colortmp > 152) {
		color = 52;
	}
	else {
		color = 53;
	}

}



void extColor() {

	for (int i = 0; i < 16; i++) {

		for (int j = 0; j < 16; j++) {
			//printf("[%2d,%2d]:%d", j, i, matArr_1[j][i]);

		}
	}
}
void colorExtract() {
	
	Mat img_color;
	Mat img_color2;
	Mat image_32;
	Mat imgGray, imgGray2;
	

	//Rect rect(140, 96, 200, 200);

	//cap.read(img_color2);
	//imshow("Cap1", img_color2);
	
	//img_color = img_color2(rect);

	//cvtColor(img_color2, imgGray2, COLOR_BGR2GRAY);
	resize(img_color2, img_color, Size(16, 16));
	//resize(imgGray2, img_color, Size(16, 16));
	//resize(img_color, image_32, Size(256, 256));
	
	imshow("Cap", img_color);
	//imshow("Cap", imgGray2);
	//imshow("Cap32", image_32);
	
	int height = img_color.rows;
	int width = img_color.cols;

	uchar* data = img_color.data;
	/*
	for (int y = 0; y < height; y++) {
		//printf("\n");
		for (int x = 0; x < width; x++) {

			colortmp = 0;
			pixel = data[y * width * 3 + x * 3];
			colortmp = pixel;
			detColor();
			tmpArr[x][y] = color;


			//printf("%d", matArr_1[x][y]);

			//cout << b << endl;

		}
		
	}

	int z = 0;
	for (int y = 1; y < 17; ++y) {
		if (y % 2 != 0) {
			for (int x = 0; x < 16; ++x) {
				z = y - 1;
				matArr_1[x][z] = tmpArr[x][z];
			}
		}
		else {
			for (int x = 15; x > -1; --x) {
				z = y - 1;
				matArr_1[x][z] = tmpArr[x][z];
			}
		}
	}
	*/
}

int main()
{

	
	char buffer;
	int tmp;
	CSerialComm serialComm; //SerialComm 객체 생성


	if (!serialComm.connect("COM5")) //COM25번의 포트를 오픈한다. 실패할 경우 -1을 반환한다.
	{
		cout << "connect faliled" << endl;
		return -1;
	}
	else
		cout << "connect successed" << endl;




	while(1){

		//colorExtract();
		

	serialComm.sendCommand('D');
	serialComm.sendCommand('O');
	delay(10);
	
	for (int x= 0; x < 16; x++) {

		for (int y = 0; y < 16; y++) {

			
			buffer = matArr_1[x][y];
			serialComm.sendCommand('C');
			serialComm.sendCommand(buffer);
			
		}
	}
	delay(300);
		if (waitKey(25) >= 0)
			break;

	}


	serialComm.disconnect(); //작업이 끝나면 포트를 닫는다

	//cout << "end connect" << endl;
	return 0;



}





