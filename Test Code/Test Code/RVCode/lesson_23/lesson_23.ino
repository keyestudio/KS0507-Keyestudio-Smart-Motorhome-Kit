/*
  keyestudio smart RV
  lesson 23
  avoiding RV
  http://www.keyestudio.com
*/
//Ultrasonic Sensor
#define EchoPin  23  //ECHO to D23
#define TrigPin  22  //TRIG to D22

//define the pins of motor A, B, C and D
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

volatile int speeds = 120;  //define the speed variable speeds
volatile int distance;
void setup() {
  pinMode(EchoPin, INPUT);  //set pin ECHO to INPUT
  pinMode(TrigPin, OUTPUT);  //set pin TRIG to OUTPUT

  //set the ports of motor to OUTPUT
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
  distance = get_distance();  //set the distance to variable distance
  if (distance < 8) {
    back();
    delay(300);
  }
  else if (distance < 15) {
    turnleft();
    delay(300);
  }
  else {
    advance();
  }
  
}

int get_distance() {  //detect distance by ultrasonic sensor
  int dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);  //trigger at least 10us high level to TRIG
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 58;  //计calculate the distance
  delay(10);
  return dis;
}
  
void advance() {    //go forward
  //Motor A rotates clockwise
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  analogWrite(PWMA, speeds);
  //Motor B rotates clockwise
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWMB, speeds);
  //Motor C rotates clockwise
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(PWMC, speeds);
  //Motor D rotates clockwise
  digitalWrite(MD1, HIGH);
  digitalWrite(MD2, LOW);
  analogWrite(PWMD, speeds);
}

void back() {   //go back
  //Motor A rotates anticlockwise
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWMA, speeds);
  //Motor B rotates anticlockwise
  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
  analogWrite(PWMB, speeds);
  //Motor C rotates anticlockwise
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(PWMC, speeds);
  //Motor D rotates anticlockwise
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, HIGH);
  analogWrite(PWMD, speeds);
}

void turnleft() {   //turn left
  //Motor A rotates clockwise
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  analogWrite(PWMA, speeds);
  //Motor B rotates anticlockwise
  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
  analogWrite(PWMB, speeds);
  //Motor C rotates anticlockwise
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(PWMC, speeds);
  //Motor D rotates clockwise
  digitalWrite(MD1, HIGH);
  digitalWrite(MD2, LOW);
  analogWrite(PWMD, speeds);
}

void turnright() {    //turn right
  //Motor A rotates anticlockwise
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWMA, speeds);
  //Motor B rotates clockwise
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWMB, speeds);
  //Motor C rotates clockwise
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(PWMC, speeds);
  //Motor D rotates anticlockwise
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, HIGH);
  analogWrite(PWMD, speeds);
}

void Stop() {   //stop
  //set the speed of four motors to 
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);
  analogWrite(PWMD, 0);
}
