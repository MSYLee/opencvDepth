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
int tmp_var[16][16];
//int x, y, z;

int numPixel = 0;
int colortmp;

//시리얼 테스트
SoftwareSerial Serial2(10,11); //시리얼통신 핀

void setup()  {

  Serial.begin(115200);
  Serial2.begin(2400);

  pixel_1.begin();
  pixel_1.show();
}

void loop() {
  // Fill along the length of the strip in various colors...
  //colorWipe_1(pixel_1.Color(255,   0,   0), 50); // Red
  if(Serial.available() > 0){
  getData();
  }
}

void getData() {
int z = 0;
  for(int y=0; y<16; ++y) {
    for(int x=0; x<16; ++x) {
        if(Serial.available() > 0){
      tmp_var[x][y] = Serial.parseInt();
      matArr_1[x][y] = tmp_var[x][y];
	  /*
      Serial.print("y=");
      Serial.print(y);
      Serial.print(", x=");
      Serial.print(x);
      Serial.print(", Array is=");
      Serial.print(matArr_1[x][y]);
          Serial.print(" ");
		  */
        }
  }
  }
  if(matArr_1[0][0] != 0){
    delay(100);
    for(int y = 1; y<17; ++y){
      if(y % 2 != 0){
        for(int x=0; x<16; ++x){
          z = y-1;
          colortmp = matArr_1[x][z];
          detColor();
          //pixel_1.show();
          numPixel++;
          Serial2.write(Serial.read());         
        }
      }
      else{
        for(int x = 15; x>-1; --x){
          z = y-1;
          colortmp = matArr_1[x][z];
          detColor();
          //pixel_1.show();
          numPixel++;
          Serial2.write(Serial.read());
        }
      }
    }
  }
}
  /*
    for(x=0; x<256; x++) {
        if(Serial.available() > 0){
          tmp_var=0;
         tmp_var =  Serial.parseInt();
         // matArr_1[x][y] = Serial.parseInt();
          colortmp = tmp_var;
          detColor();
          pixel_1.show();
      
       // Serial.print(matArr_1[x][y]);
        //Serial.print(" ");
        
          numPixel++;
          Serial2.write(Serial.read());
        }
    }
  */



void detColor(){
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
/*
void setColor(){
   pixel_1.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    pixel_1.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
*/
