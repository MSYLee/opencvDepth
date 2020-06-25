#include <Adafruit_NeoPixel.h>
#include "DepthSerialLib.h"

#define PIN1 6  //connect 12 Neopixel strip to Digital PIN6

#define LED_COUNT 256

Adafruit_NeoPixel pixel_1 = Adafruit_NeoPixel(LED_COUNT, PIN1, NEO_GRB + NEO_KHZ800);



int matArr_1[16][16];


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
    displayData();
  }
}



void getData() {
  pixel_1.clear();
  pixel_1.show();
 if (Serial.find("D")) {
  for (int x = 0; x < 16; ++x) {
    if (Serial.find("C")) {
    for (int y = 0; y < 16; ++y) {
      
        matArr_1[x][y] = Serial.parseInt();
      }
      else {
        matArr_1[x][y] = 6;
      }
    
  }
  
  modetmp = 3;
}
}

}
void displayData() {

  for (int x = 0; x < 16; x++) {
    for (int y = 0; y < 16; y++) {
      colortmp = matArr_1[x][y];
      if (colortmp == 1) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(5, 5, 0));
       }
      else if (colortmp == 2) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(0, 0, 0));
      }
      else if (colortmp == 3) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(5, 5, 5));
      }
      else if (colortmp == 4) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(5, 5, 0));
      }
      else if (colortmp == 6) {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(1, 1, 1));
      }
      else {
        pixel_1.setPixelColor(numPixel, pixel_1.Color(5, 0, 0));
      }
      numPixel++;
    }
    pixel_1.show();
  }

  numPixel = 0;
  modetmp = 2;
}
