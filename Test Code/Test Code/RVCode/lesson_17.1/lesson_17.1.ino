/*
  keyestudio smart RV
  lesson 17.1
  2812 led
  http://www.keyestudio.com
*/
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel rgb_2812 = Adafruit_NeoPixel(10, 53, NEO_GRB + NEO_KHZ800); //dset the port of 10 pcs lights to 53, with GRB mode

void setup() {
  rgb_2812.begin();
}

void loop () {

  for (int i = 0; i <= 9; i++) {
    rgb_2812.setPixelColor(i,255,0,0);  //the first light shows red color
    rgb_2812.show();                    //show
    delay(50);
  }
  for (int i = 9; i >= 0; i--) {
    rgb_2812.setPixelColor(i, 0,0,0);   //the first light turns off
    rgb_2812.show();                    //show
    delay(50);
  }

  for (int i = 0; i <= 9; i++) {
    rgb_2812.setPixelColor(i,0,255,0);  //the first light shows green color
    rgb_2812.show();                    //show
    delay(50);
  }
  for (int i = 9; i >= 0; i--) {
    rgb_2812.setPixelColor(i, 0,0,0);   //the first light turns off
    rgb_2812.show();                    //display
    delay(50);
  }

  for (int i = 0; i <= 9; i++) {
    rgb_2812.setPixelColor(i,0,0,255);  //the first light shows blue color
    rgb_2812.show();                    //show
    delay(50);
  }
  for (int i = 9; i >= 0; i--) {
    rgb_2812.setPixelColor(i, 0,0,0);   //the first light turns off
    rgb_2812.show();                    //show
    delay(50);
  }

}
