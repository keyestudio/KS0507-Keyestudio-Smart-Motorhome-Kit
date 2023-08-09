/*
  keyestudio smart RV
  lesson 14.2
  servo
  http://www.keyestudio.com
*/
#include <Servo.h>  //include the library code:
Servo myservo;

void setup() {
  myservo.attach(8);  //connect servo to digital 8

}

void loop () {
  //rotate 0° to 180°
  for (int i = 0; i < 180; i++) {
    myservo.write(i);
    delay(20);
  }
  delay(1000);  //delay in 1s

  //rotate from 180° to 0°
  for (int i = 180; i > 0; i--) {
    myservo.write(i);
    delay(20);
  }
  delay(1000);  //delay in 1s
}
