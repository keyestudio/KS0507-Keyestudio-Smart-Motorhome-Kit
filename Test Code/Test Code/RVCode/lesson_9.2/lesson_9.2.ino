/*
  keyestudio smart RV
  lesson 9.2
  Adjustable potentiometer
  http://www.keyestudio.com
*/
#define RES A3   //set potentiometer pin to A3
#define LED 13   //define the pin of LED as D13
volatile int value = 0;
void setup() {
  pinMode(LED, OUTPUT);// initialize digital pin LED as an output.
}

void loop () {
  value = analogRead(RES);  //read the value of potentiometer 
  int light = map(value, 0, 1023, 0, 255); //map the analog value 0~1023 of potentiometer to 0~255
  analogWrite(LED, light);   //set LED brightness to light
  delay(100);               //delay in 100MS
}
