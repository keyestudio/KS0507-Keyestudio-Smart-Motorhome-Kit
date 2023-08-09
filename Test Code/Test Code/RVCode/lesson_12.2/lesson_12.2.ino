/*
  keyestudio smart RV
  lesson 12.2
  MQ2
  http://www.keyestudio.com
*/
#define MQ2_A   A0  // define MQ2_A as A0
#define MQ2_D   A1  //define MQ2_A as A1
#define buzzer  49 //buzzer pin to D49
volatile int analogVal, digitalVal;

void setup() {
  Serial.begin(9600);

}

void loop () {
  analogVal = analogRead(MQ2_A);  //read the analog value
  Serial.println(analogVal);      //print the value of sensor
  if (analogVal > 150) {          //when analog value exceeds 150, the buzzer will alarm
    tone(buzzer, 1000);
  }
  else {
    noTone(buzzer); //turn off buzzer
  }
  delay(100);

}
