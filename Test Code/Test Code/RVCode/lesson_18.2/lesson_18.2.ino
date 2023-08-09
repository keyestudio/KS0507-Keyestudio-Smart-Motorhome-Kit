/*
  keyestudio smart RV
  lesson 18.2
  motor
  http://www.keyestudio.com
*/
//define the pins of motor A,B,C and D
const int MA1 = 35;
const int MA2 = 34;
const int PWMA = 12;

const int MB1 = 33;
const int MB2 = 32;
const int PWMB = 11;

const int MC1 = 29;
const int MC2 = 28;
const int PWMC = 9;

const int MD1 = 31;
const int MD2 = 30;
const int PWMD = 10;

void setup() {
  //set the pins of motor to OUTPUT
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);

  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);

  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);

  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);

}

void loop () {
  //go forward for 1s
  advance();
  delay(1000);
  //go back for 1s
  back();
  delay(1000);
  //turn left for 1s
  turnleft();
  delay(1000);
  //turn right for 1s
  turnright();
  delay(1000);
  //stop 1s
  Stop();
  delay(1000);
}

void advance() {    //go forward
  // motor A rotates clockwise
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  analogWrite(PWMA, 150);
  //motor B rotates clockwise
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWMB, 150);
  //motor C rotates clockwise
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(PWMC, 150);
  //motor D rotates clockwise
  digitalWrite(MD1, HIGH);
  digitalWrite(MD2, LOW);
  analogWrite(PWMD, 150);
}

void back() {   //go back
  //motor A rotates anticlockwise
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWMA, 150);
  //motor B rotates anticlockwise
  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
  analogWrite(PWMB, 150);
  //motor C rotates anticlockwise
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(PWMC, 150);
  //motor D rotates anticlockwise
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, HIGH);
  analogWrite(PWMD, 150);
}

void turnleft() {   //turn left
  //motor A rotates clockwise
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  analogWrite(PWMA, 150);
  //motor B rotates anticlockwise
  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
  analogWrite(PWMB, 150);
  //motor C rotates anticlockwise
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(PWMC, 150);
  //motor D rotates clockwise
  digitalWrite(MD1, HIGH);
  digitalWrite(MD2, LOW);
  analogWrite(PWMD, 150);
}

void turnright() {    //turn right
  //motor A rotates anticlockwise
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWMA, 150);
  //motor B rotates clockwise
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWMB, 150);
  //motor C rotates clockwise
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(PWMC, 150);
  //motor D rotates anticlockwise
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, HIGH);
  analogWrite(PWMD, 150);
}

void Stop() {   //Car stops
  //set the speed of four motors to 0
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);
  analogWrite(PWMD, 0);
}
