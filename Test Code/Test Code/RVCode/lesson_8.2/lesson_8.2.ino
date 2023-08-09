/*
  keyestudio smart RV
  lesson 8.2
  RGB
  http://www.keyestudio.com
*/

#define RGB_R  3  //define the pin R of RGB as D3
#define RGB_B  4  //set pin B of RGB to D4
#define RGB_G  5  //set pin g of RGB to D5
int r, g, b;
void setup() {
  pinMode(RGB_R, OUTPUT); // set digital ports of RGB to OUTPUT
  pinMode(RGB_G, OUTPUT);
  pinMode(RGB_B, OUTPUT);
}

void loop () {
  //choose a random number from 0 to 255
  r = random(255);  
  g = random(255);
  b = random(255);
  set_RGBColor(r, g, b); //random colors
  delay(500);
}

//set color
void set_RGBColor(int red, int green, int blue) {
  analogWrite(RGB_R, red);
  analogWrite(RGB_G, green);
  analogWrite(RGB_B, blue);
}
