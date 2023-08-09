/*
  keyestudio smart RV
  lesson 14.1
  servo
  http://www.keyestudio.com
*/
int servoPin = 8; //pin of servo

void setup() {
  pinMode(servoPin, OUTPUT);//set the pin of servo to OUTPUT
}
void loop() {
  servopulse(servoPin, 0);//rotate to 0°
  delay(1000);//delay 1s
  servopulse(servoPin, 90);//rotate to 900°
  delay(1000);
  servopulse(servoPin, 180);//rotate to 180°
  delay(1000);
}

void servopulse(int pin, int myangle) { //output function
  int pulsewidth = map(myangle, 0, 180, 500, 2500); //map angle to pulsewidth
  for (int i = 0; i < 10; i++) { //output pulse
    digitalWrite(pin, HIGH);//set level of servo port to HIGH
    delayMicroseconds(pulsewidth);//delay the time of pulsewidth
    digitalWrite(pin, LOW);//set the level of servo port to LOW
    delay(20 - pulsewidth / 1000);
  }
}
