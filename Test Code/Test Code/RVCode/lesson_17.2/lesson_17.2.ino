/*
  keyestudio smart RV
  lesson 17.2
  2812 led
  http://www.keyestudio.com
*/
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel rgb_2812 = Adafruit_NeoPixel(10, 53, NEO_GRB + NEO_KHZ800); //set the port of 10 pcs lights to 53, with GRB mode

void setup() {
  rgb_2812.begin();
}

void loop () {
  rainbow(20);  //keep gradient color for 20ms

}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i <= 9; i++) {
      rgb_2812.setPixelColor(i, Wheel((i + j) & 255));
    }
    rgb_2812.show(); //display
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) { //set color
  if (WheelPos < 85) {
    return rgb_2812.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return rgb_2812.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return rgb_2812.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
