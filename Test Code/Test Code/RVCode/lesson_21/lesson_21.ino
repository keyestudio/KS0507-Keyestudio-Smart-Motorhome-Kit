/*
  keyestudio smart RV
  lesson 21
  Thacking RV
  http://www.keyestudio.com
*/
//Line Tracking Sensor
#define L_pin  50
#define M_pin  51
#define R_pin  52

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
void setup() {
  pinMode(L_pin, INPUT); //set the pins of line tracking sensor to INPUT
  pinMode(M_pin, INPUT);
  pinMode(R_pin, INPUT);

  //set ports of motor to OUTPUT
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
  int L_val = digitalRead(L_pin); //read the value of left sensor
  int M_val = digitalRead(M_pin); //read the value of middle sensor
  int R_val = digitalRead(R_pin); //read the value of right sensor
  if (M_val == 1) { //the middle one detects black line
    if (L_val == 1 && R_val == 0) { //if only left sensor detects black line, turn left
      turnleft();
    }
    else if (L_val == 0 && R_val == 1) { //if only right sensor detects black line, turn right
      turnright();
    }
    else { //go forward
      advance();
    }
  }
  else { //the middle sensor detects black line
    if (L_val == 1 && R_val == 0) { //if only left sensor detects black line, turn left
      turnleft();
    }
    else if (L_val == 0 && R_val == 1) { //if only right sensor detects black line，turn right
    }
    else { //stop
      Stop();
    }
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
