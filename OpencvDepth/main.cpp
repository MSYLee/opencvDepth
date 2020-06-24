
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <sstream>

#include <stdio.h>
#include <string>
#include <fstream>

#include <time.h>

#include "serialcomm.h"
#include "NtKinect.h"




using namespace cv;
using namespace std;

Mat DIG, DIG2;
//Mat frame;

char buffer;

uchar* pData;
int height = 0;
int width = 0;

int pixel;
int color;
int colortmp;

int rep = 0;

char matArr_1[16][16];
char matArr_2[16][16];
char matArr_3[16][16];
char matArr_4[16][16];
char matArr[32][32];




/*
void doJob2() {
	NtKinect kinect;
	while (1) {
		kinect.setDepth(false);
		DIG = kinect.depthImage;
		cv::imshow("Depth", DIG);
		//cv::imshow("depth", kinect.depthImage);
		auto key = cv::waitKey(1);
		if (key == 'q') break;
	}
	cv::destroyAllWindows();
}
*/


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

void singleMatrix() {

	pData = DIG2.data;

	height = DIG2.rows;
	width = DIG2.cols;

	for (int y = 0; y < height; y++) {

		cout<<"\n"<<endl;
		for (int x = 0; x < width; x++) {

			colortmp = 0;
			pixel = pData[y * width * 3 + x * 3];
			colortmp = pixel;
			detColor();
			matArr_1[x][y] = color;

			matArr[x][y] = matArr_1[x][y];

			printf("%c", matArr[x][y]);

		}
	}
}

void multiMatrix() {

	pData = DIG2.data;

	height = DIG2.rows;
	width = DIG2.cols;

	for (int y = 0; y < height; y++) {
		int i = 0;
		int j = 0;

		//printf("StartProgress\n");
		printf("\n");
		for (int x = 0; x < width; x++) {
			//printf("\n");
			
			//printf("\n1st%d\n", i);
			//printf("\nj is%d\n", j);
			//i = i / j;
			//printf("\n2nd%d\n", i);

			if (i < 16) {
				//printf("1St if\n");
				colortmp = 0;
				pixel = pData[y * width * 3 + x * 3];
				colortmp = pixel;
				detColor();
				matArr[x][y] = color;
				printf("%c", matArr[x][y]);
				//printf("%d",i);
			}
			else if (i > 15) {
				//printf("\n");

				colortmp = 0;
				pixel = pData[y * width * 3 + x * 3];
				colortmp = pixel;
				detColor();
				matArr[x][y] = color;
				printf(" %c", matArr[x][y]);
				//printf(" %d", i);
			}
			else {
				printf("Error!!");
				printf("\n\nI is %d\n\n", i);
			}

			i++;

		}
	}

}


/*
void extColor() {

	for (int i = 0; i < 16; i++) {

		for (int j = 0; j < 16; j++) {
			//printf("[%2d,%2d]:%d", j, i, matArr_1[j][i]);

		}
	}
}
*/

void colorExtract() {
	pData = DIG2.data;

	height = DIG2.rows;
	width = DIG2.cols;

	//cout << "Start" << endl;
	for (int y = 0; y < height; y++) {
		/*
		cout << "Y is = " << endl;
		cout << y << endl;
		*/
		//printf("\n");

		for (int x = 0; x < width; x++) {

			colortmp = 0;
			pixel = pData[y * width * 3 + x * 3];
			colortmp = pixel;
			detColor();
			matArr_1[x][y] = color;


			//printf("%d", matArr_1[x][y]);
			/*
			cout << "x is = " << endl;
			cout << x << endl;
			cout << matArr_1[x][y] << endl;
			*/
		}
	}
	cout << "End" << endl;
}




int serialConnect()
{
	CSerialComm serialComm; //SerialComm 객체 생성


	if (!serialComm.connect("COM6")) //COM25번의 포트를 오픈한다. 실패할 경우 -1을 반환한다.
	{
		cout << "connect faliled" << endl;
		return -1;
	}
	else
		cout << "connect successed" << endl;






	for (int y = 0; y < height; y++) {
		serialComm.sendCommand('\n');
		//printf("\n");
		for (int x = 0; x < width; x++) {

			buffer = matArr[x][y];
			//serialComm.sendCommand('\n');
			printf("%c", matArr[x][y]);
			printf("%c", buffer);

			delay(10);

			if (!serialComm.sendCommand(buffer))
			{
				cout << "send command failed" << endl;
			}
			else

				cout << "send Command success" << endl;

			//rep = 1;

		}
	}




	//serialComm.disconnect(); //작업이 끝나면 포트를 닫는다

	//cout << "end connect" << endl;
	return 0;

}


void jobTest() {
	DIG2 = imread("Image32.png", IMREAD_COLOR);
	if (DIG2.empty()) {
		cout << "Cant read Image" << endl;
	}
	imshow("Shif77L", DIG2);

	//singleMatrix();
	multiMatrix();

	//colorExtract();

	//serialConnect();
}

void doJob() {

	NtKinect kinect;

	while (1) {

		kinect.setDepth(false);
		DIG = kinect.depthImage;
		//cv::imshow("Depth", DIG);

		cv::rectangle(DIG, cv::Point(140, 96), cv::Point(372, 328), cv::Scalar(255, 0, 0), 3, 1, 0);
		imshow("Point", DIG);

		Rect rect(140, 96, 200, 200);
		DIG2 = DIG(rect);
		resize(DIG, DIG2, Size(16, 16));

		imshow("NEW", DIG2);

		colorExtract();

		serialConnect();
		
		//delay(10000);

		//cout << width << endl;
		//cout << height << endl;



		auto key = cv::waitKey(1);
		if (key == 'q') break;
	}


	//kinect.depthImage >> DIG;
}



int main() {
	jobTest();
}



/*
int main(int argc, char** argv) {

	try {
		jobTest();
	}
	catch (exception &ex) {
		cout << ex.what() << endl;
		string s;
		cin >> s;
	}
	return 0;
}
*/