
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
  {50, 50, 50, 50, 50, 50, 50, 51, 51, 50, 50, 50, 50, 50, 50, 50},
  {50, 50, 50, 50, 50, 50, 51, 49, 49, 51, 50, 50, 50, 50, 50, 50},
  {50, 50, 50, 50, 50, 50, 51, 49, 49, 51, 50, 50, 50, 50, 50, 50},
  {50, 50, 50, 50, 50, 51, 49, 49, 49, 49, 51, 50, 50, 50, 50, 50},
  {51, 51, 51, 51, 51, 51, 49, 49, 49, 49, 51, 51, 51, 51, 51, 51},
  {51, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 51},
  {51, 51, 49, 49, 49, 51, 51, 49, 49, 51, 51, 49, 49, 49, 51, 51},
  {50, 50, 51, 49, 49, 51, 51, 49, 49, 51, 51, 49, 49, 51, 50, 50},
  {50, 50, 50, 51, 49, 51, 51, 49, 49, 51, 51, 49, 51, 50, 50, 50},
  {50, 50, 50, 51, 49, 51, 51, 49, 49, 51, 51, 49, 51, 50, 50, 50},
  {50, 50, 51, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 51, 50, 50},
  {50, 50, 51, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 51, 50, 50},
  {50, 51, 49, 49, 49, 49, 49, 51, 51, 49, 49, 49, 49, 49, 51, 50},
  {51, 51, 49, 49, 49, 51, 51, 50, 50, 51, 51, 49, 49, 49, 51, 51},
  {51, 49, 49, 51, 51, 50, 50, 50, 50, 50, 50, 51, 51, 49, 49, 51},
  {51, 51, 51, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 51, 51, 51}
};

int matArr_2[16][16] = {
  {50, 50, 50, 50, 50, 50, 50, 49, 49, 50, 50, 50, 50, 50, 50, 50},
  {50, 50, 50, 50, 50, 50, 49, 50, 50, 49, 50, 50, 50, 50, 50, 50},
  {50, 50, 50, 50, 50, 50, 49, 50, 50, 49, 50, 50, 50, 50, 50, 50},
  {50, 50, 50, 50, 50, 49, 50, 50, 50, 50, 49, 50, 50, 50, 50, 50},
  {49, 49, 49, 49, 49, 49, 50, 50, 50, 50, 49, 49, 49, 49, 49, 49},
  {49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 49},
  {49, 49, 50, 50, 50, 49, 49, 50, 50, 49, 49, 50, 50, 50, 49, 49},
  {50, 50, 49, 50, 50, 49, 49, 50, 50, 49, 49, 50, 50, 49, 50, 50},
  {50, 50, 50, 49, 50, 49, 49, 50, 50, 49, 49, 50, 49, 50, 50, 50},
  {50, 50, 50, 49, 50, 49, 49, 50, 50, 49, 49, 50, 49, 50, 50, 50},
  {50, 50, 49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 49, 50, 50},
  {50, 50, 49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 49, 50, 50},
  {50, 49, 50, 50, 50, 50, 50, 49, 49, 50, 50, 50, 50, 50, 49, 50},
  {49, 49, 50, 50, 50, 49, 49, 50, 50, 49, 49, 50, 50, 50, 49, 49},
  {49, 50, 50, 49, 49, 50, 50, 50, 50, 50, 50, 49, 49, 50, 50, 49},
  {49, 49, 49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 49, 49, 49}
};

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
	else if (colortmp < 102 && colortmp < 50) {
		color = 50;
	}
	else if (colortmp < 153 && colortmp < 101) {
		color = 51;
	}
	else if (colortmp < 204 && colortmp < 152) {
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

	Mat img_color = imread("Image.png", IMREAD_COLOR);

	int height = img_color.rows;
	int width = img_color.cols;

	uchar* data = img_color.data;

	for (int y = 0; y < height; y++) {
		//printf("\n");
		for (int x = 0; x < width; x++) {

			colortmp = 0;
			pixel = data[y * width * 3 + x * 3];
			colortmp = pixel;
			detColor();
			matArr_1[x][y] = color;


			//printf("%d", matArr_1[x][y]);

			//cout << b << endl;

		}
	}

}




int main()
{

	//colorExtract();

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


		

	serialComm.sendCommand('D');
	serialComm.sendCommand('O');
	delay(10);

	for (int x= 0; x < 16; x++) {

		for (int y = 0; y < 16; y++) {

			
			buffer = matArr_1[x][y];
			serialComm.sendCommand('C');
			serialComm.sendCommand(buffer);
			//delay(1);
		}
	}
	  

	delay(1000);


	serialComm.sendCommand('D');
	serialComm.sendCommand('O');
	delay(10);

	for (int x = 0; x < 16; x++) {

		for (int y = 0; y < 16; y++) {


			buffer = matArr_2[x][y];
			serialComm.sendCommand('C');
			serialComm.sendCommand(buffer);
			//delay(1);
		}
	}

	delay(1000);
	}


	serialComm.disconnect(); //작업이 끝나면 포트를 닫는다

	//cout << "end connect" << endl;
	return 0;



}





