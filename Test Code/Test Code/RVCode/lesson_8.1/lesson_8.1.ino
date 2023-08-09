/*
  keyestudio smart RV
  lesson 8.1
  RGB
  http://www.keyestudio.com
*/

#define RGB_R  3  //define pin R of RGB as D3
#define RGB_B  4  // define pin B of RGB as D4
#define RGB_G  5  //define pin B of RGB as D5

void setup() {
  pinMode(RGB_R, OUTPUT); //set the digital ports to OUTPUT
  pinMode(RGB_G, OUTPUT);
  pinMode(RGB_B, OUTPUT);
}

void loop () {
  set_RGBColor(0,255,255);   //red
  delay(500);
  set_RGBColor(255,0,255);   //green
  delay(500);
  set_RGBColor(255,255,0);   //blue
  delay(500);
}

//set color
void set_RGBColor(int red, int green, int blue) {
  analogWrite(RGB_R, red);
  analogWrite(RGB_G, green);
  analogWrite(RGB_B, blue);
}
