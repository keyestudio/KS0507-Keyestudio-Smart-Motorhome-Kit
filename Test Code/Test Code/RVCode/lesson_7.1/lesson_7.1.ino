/*
  keyestudio smart car
  lesson 7.1
  buzzer
  http://www.keyestudio.com
*/

#define buzzer 49 //buzzer pin to D49

void setup() {
  pinMode(buzzer, OUTPUT);//set digital 49 to OUTPUT
}

void loop () {
  tone(buzzer, 262);  //buzzer emits the sound with 262Hz
  delay(250);   //delay in 250ms
  tone(buzzer, 294);;   //buzzer emits the sound with 294Hz
  delay(250);   //delay in 250ms
  tone(buzzer, 330);
  delay(250);
  tone(buzzer, 349);
  delay(250);
  tone(buzzer, 392);
  delay(250);
  tone(buzzer, 440);
  delay(250);
  tone(buzzer, 494);
  delay(250);
  tone(buzzer, 532);
  delay(250);
  noTone(buzzer);   //buzzer turns off sound output
  delay(1000);
}
