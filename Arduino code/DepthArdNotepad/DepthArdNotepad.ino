#include <Adafruit_NeoPixel.h>
#include "DepthSerialLib.h"

#define PIN1 6  //connect 12 Neopixel strip to Digital PIN6

#define LED_COUNT 256

Adafruit_NeoPixel pixel_1 = Adafruit_NeoPixel(LED_COUNT, PIN1, NEO_GRB + NEO_KHZ800);



int matArr_1[16][16];
int tmpArr[16][16];


int numPixel = 0;
int colortmp;


void setup()  {

  Serial.begin(115200);
  Serial.setTimeout(2);


  pixel_1.begin();
  pixel_1.clear();
  pixel_1.show();

  Serial.println("------Arduino Ready-------");
  Serial.print("Wait for Serial input\n");


}

void loop() {
  // Fill along the length of the strip in various colors...
  //colorWipe_1(pixel_1.Color(255,   0,   0), 50); // Red


  if (modetmp == 1) {
    readdata();

  }
  else if (modetmp == 2) {
    getData();
  }
  else if (modetmp == 3) {
    //calcData();
    displayData();
  }
}


void getData() {

  for (int x = 0; x < 16; ++x) {
    for (int y = 0; y < 16; ++y) {
      if (Serial.find("C")) {
        matArr_1[x][y] = Serial.parseInt();
      }
      else {
        matArr_1[x][y] = 1;
      }
    }
  }
  modetmp = 3;
}


void calcData() {
  

  int z = 0;
  if(tmpArr[0][0] != 0){
    for(int y = 1; y<17; ++y){
      if(y % 2 != 0){
        for(int x=0; x<16; ++x){
          z = y-1;
          matArr_1[x][z] = tmpArr[x][z];         
        }
      }
      else{
        for(int x = 15; x>-1; --x){
          z = y-1;
          matArr_1[x][z] = tmpArr[x][z];
        }
      }
    }
  }

}


void displayData() {

  //pixel_1.clear();
  //pixel_1.show();

  for (int x = 0; x < 16; x++) {
    for (int y = 0; y < 16; y++) {
      colortmp = matArr_1[x][y];
      if (colortmp == 1) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(0, 0, 0));
       }
      else if (colortmp == 2) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(3, 3, 3));
      }
      else if (colortmp == 3) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(5, 5, 5));
      }
      else if (colortmp == 4) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(7, 7, 7));
      }
      else if (colortmp == 5) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(9, 9, 9));
      }
      else {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(12, 12, 12));
      }
      numPixel++;
    }
    pixel_1.show();
  }

  numPixel = 0;
  modetmp = 1;
}
