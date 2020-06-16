#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define PIN1 6  //connect 12 Neopixel strip to Digital PIN6
//#define PIN2 5  //connect 6 Neopixel strip to Digital PIN7

#define LED_COUNT 256

Adafruit_NeoPixel pixel_1 = Adafruit_NeoPixel(LED_COUNT, PIN1, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixel_2 = Adafruit_NeoPixel(LED_COUNT, PIN2, NEO_GRB + NEO_KHZ800);

int delayval = 10; // timing delay
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

int matArr_1[16][16];
int x, y;

int numPixel = 0;
int colortmp;

//시리얼 테스트
SoftwareSerial mySerial(10,11); //시리얼통신 핀

void setup()  {

  Serial.begin(9600);
  mySerial.begin(2400);

  pixel_1.begin();
  pixel_1.show();
}

void loop() {
  // Fill along the length of the strip in various colors...
  //colorWipe_1(pixel_1.Color(255,   0,   0), 50); // Red
  
  getData();
  
}

void getData() {
  
  for(y=0; y<16; y++) {
    for(x=0; x<16; x++) {
        if(Serial.available() > 0){
          matArr_1[x][y] = Serial.parseInt();
          colortmp = matArr_1[x][y];
          detColor();
          pixel_1.show();
      
       // Serial.print(matArr_1[x][y]);
        //Serial.print(" ");
        
          numPixel++;
          mySerial.write(Serial.read());
        }
    }
  }
}

void detColor(){
  if (colortmp == 1) {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(0, 0, 20));
    }
  else if (colortmp == 2) {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(0, 10, 10));
    }
  else if (colortmp == 3) {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(0, 20, 0));
    }
  else if (colortmp == 4) {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(10, 10, 0));
    }
  else {
    pixel_1.setPixelColor(numPixel, pixel_1.Color(20, 0, 0));
    }
}
/*
void setColor(){
   pixel_1.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    pixel_1.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
*/
