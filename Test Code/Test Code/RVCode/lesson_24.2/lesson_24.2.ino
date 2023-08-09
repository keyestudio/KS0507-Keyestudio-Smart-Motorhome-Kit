/*
  keyestudio smart RV
  lesson 24.2
  blutooth control RV
  http://www.keyestudio.com
*/

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
char ble_val;   //set variable ble_val

void setup() {
  Serial1.begin(9600);  //set Bluetooth baud rate to 9600
  Serial.begin(9600);
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
  if (Serial1.available() > 0) //serial port reads characters
  {
    ble_val = Serial1.read();//set the character read by serial port to val
    switch (ble_val) {
      case 'F':  advance();    break;
      case 'B':  back();       break;
      case 'L':  turnleft();   break;
      case 'R':  turnright();  break;
      case 'S':  Stop();       break;
      case  'W':  speeds_a();  break;  //receive ‘W’, speed up
      case  'Z':  speeds_d();  break; //receive "Z", speed down
    }
  }
  
}

void speeds_a() { //increment function
  int a_flag = 1; //used for while loop
  while (a_flag) {
    Serial.println(speeds);  //display velocity
    if (speeds < 255) { //increase to 255(MAX)
      speeds++;
      delay(15);  //adjust the rate of acceleration
    }
    ble_val = Serial1.read();
    if (ble_val == 'S')a_flag = 0; //receive‘S’, stop speeding up
  }
}

void speeds_d() { //Deceleration function
  int d_flag = 1; //used for while loop
  while (d_flag) {
    Serial.println(speeds);  //display speed
    if (speeds > 0) { //decrease to 0
      speeds--;
      delay(15);    //adjust the rate of deceleration
    }
    ble_val = Serial1.read();
    if (ble_val == 'S')d_flag = 0; //receive ‘S’and stop speeding down
  }
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
  //set the speed of four motors to 0
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);
  analogWrite(PWMD, 0);
}
