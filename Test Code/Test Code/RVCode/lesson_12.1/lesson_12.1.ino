/*
  keyestudio smart RV
  lesson 12.1
  MQ2
  http://www.keyestudio.com
*/
#define MQ2_A   A0  //define the pin mq2 as A0
#define MQ2_D   A1  //define the pin mq2 as A1
volatile int analogVal,digitalVal;

void setup() {
  Serial.begin(9600);

}

void loop () {
  digitalVal = digitalRead(MQ2_D);  //read the digital value
  analogVal = analogRead(MQ2_A);  //read the analog value
  Serial.print("digitalVal:");
  Serial.print(digitalVal);
  Serial.print("  analogVal:");
  Serial.println(analogVal);
  delay(100);

}
