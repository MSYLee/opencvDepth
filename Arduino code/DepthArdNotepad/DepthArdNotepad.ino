#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include "DepthSerialLib.h"

#define PIN1 6  //connect 12 Neopixel strip to Digital PIN6
//#define PIN2 5  //connect 6 Neopixel strip to Digital PIN7

#define LED_COUNT 256

Adafruit_NeoPixel pixel_1 = Adafruit_NeoPixel(LED_COUNT, PIN1, NEO_GRB + NEO_KHZ800);


int delayval = 10; // timing delay
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

int matArr_1[16][16];
int tmp_var[16][16];

int numPixel = 0;
int colortmp;




//시리얼 테스트
SoftwareSerial Serial2(10, 11); //시리얼통신 핀

void setup()  {

  Serial.begin(115200);
  //Serial2.begin(2400);
 Serial.setTimeout(10);


  pixel_1.begin();
  pixel_1.show();

  Serial.println("------Arduino Ready-------");
  Serial.print("Wait for Serial input\n");


}

void loop() {
  // Fill along the length of the strip in various colors...
  //colorWipe_1(pixel_1.Color(255,   0,   0), 50); // Red

    if (modetmp == 0) {
      SessionTest();
    }
    else if (modetmp == 1) {
      readdata();
      
    }
    else if (modetmp == 2) {
      getData();
    }
  }





void getData() {

    Serial.println("====GETDATA=====");
    for (int y = 0; y < 16; ++y) {
      for (int x = 0; x < 16; ++x) {
        
        if (Serial.find("\n")) {
          tmp_var[x][y] = Serial.parseInt();
          matArr_1[x][y] = tmp_var[x][y];
            Serial.print("matArr_1[");
            Serial.print(x);
            Serial.print("][");
            Serial.print(y);
            Serial.print("] :[");
            Serial.print(tmp_var[x][y]);
            Serial.print("]\n");  
        } 
        else {
            Serial.print("matArr_1[");
            Serial.print(x);
            Serial.print("][");
            Serial.print(y);
            Serial.print("] :[");
            Serial.print("error");
            Serial.print("]\n");
        }

      }
    }
  
  Serial.println("====DONE=====");
  modetmp = 0;
}





void detColor() {
  if (colortmp == 1) {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(0, 0, 20));
    pixel_1.show();
  }
  else if (colortmp == 2) {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(0, 10, 10));
    pixel_1.show();
  }
  else if (colortmp == 3) {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(0, 20, 0));
    pixel_1.show();
  }
  else if (colortmp == 4) {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(10, 10, 0));
    pixel_1.show();
  }
  else {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(20, 0, 0));
    pixel_1.show();
  }
}
