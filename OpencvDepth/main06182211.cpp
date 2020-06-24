
#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>

#include <stdio.h>
#include <string>
#include <time.h>

#include "serialcomm.h"
#include "NtKinect.h"




using namespace cv;
using namespace std;

Mat DIG;

int pixel;
int color;
int colortmp;

char matArr_1[16][16];

void doJob() {
	NtKinect kinect;
	kinect.setDepth(false);
	DIG = kinect.depthImage;
}


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

	doJob();

	int height = DIG.rows;
	int width = DIG.cols;

	uchar* data = DIG.data;

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

	colorExtract();

	char buffer;
	CSerialComm serialComm; //SerialComm ��ü ����


	if (!serialComm.connect("COM6")) //COM25���� ��Ʈ�� �����Ѵ�. ������ ��� -1�� ��ȯ�Ѵ�.
	{
		cout << "connect faliled" << endl;
		return -1;
	}
	else
		cout << "connect successed" << endl;






	for (int y = 0; y < 16; y++) {
		serialComm.sendCommand('\n');
		//printf("\n");
		for (int x = 0; x < 16; x++) {

			
			buffer = matArr_1[x][y];
			serialComm.sendCommand('\n');
			//printf("%c", buffer);
			
			delay(10);
			
			if (!serialComm.sendCommand(buffer))
			{
				cout << "send command failed" << endl;
			}
			else
				
				cout << "send Command success" << endl;
			
		}
	}




	serialComm.disconnect(); //�۾��� ������ ��Ʈ�� �ݴ´�

	//cout << "end connect" << endl;
	return 0;



}






/*
int main(int argc, char** argv) {
	try {
		doJob();
	}
	catch (exception &ex) {
		cout << ex.what() << endl;
		string s;
		cin >> s;
	}
	return 0;
}
*/