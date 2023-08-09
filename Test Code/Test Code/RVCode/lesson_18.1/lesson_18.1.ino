/*
  keyestudio smart RV
  lesson 18.1
  motor
  http://www.keyestudio.com
*/
//define the pins of motor
const int Motor1 = 31;
const int Motor2 = 30;
const int PWM = 10;

void setup() {
  //set ports of motor to OUTPUT
  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);

}

void loop () {
  //rotate anticlockwise for 1
  digitalWrite(Motor1, HIGH);
  digitalWrite(Motor2, LOW);
  analogWrite(PWM, 100);
  delay(2000);
  //rotate clockwise for 1s
  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, HIGH);
  analogWrite(PWM, 100);
  delay(2000);
  //stop 1s
  analogWrite(PWM, 0);
  delay(1000);
}
