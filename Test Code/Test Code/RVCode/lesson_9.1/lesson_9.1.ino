/*
  keyestudio smart RV
  lesson 9.1
  Adjustable potentiometer
  http://www.keyestudio.com
*/
#define RES  A3   //potentiometer pin to A3
volatile int value=0;
void setup() {
  Serial.begin(9600);//set baud rate
}

void loop () {
  value = analogRead(RES);  //read the value of potentiometer
  Serial.println(value);    //print value
  delay(100);               //delay in 100MS
}
