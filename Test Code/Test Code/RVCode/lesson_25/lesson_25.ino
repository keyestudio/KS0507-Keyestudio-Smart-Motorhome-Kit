/*
  keyestudio smart RV
  lesson 25
  Smart RV
  http://www.keyestudio.com
*/
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel rgb_2812 = Adafruit_NeoPixel(10, 53, NEO_GRB + NEO_KHZ800);

const int door_servo = 6;        //connect servo of door to D6
const int trunk_servo = 7;       //connect servo of sunroof to D7
const int skylight_servo = 8;    //connect the servo of trunk to D8

#include <dht11.h>    //include the library code:
dht11 DHT;
#define DHT11_PIN 48  //define DHT11 as digital 48

#include <Wire.h>
#include <LiquidCrystal_I2C.h>      // includes the LiquidCrystal_I2C Library 
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD addrecount to 0x27 for a 16 chars and 2 line display

#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keyprecounted;     //used to receive the key value
//define the cymbols on the buttons of the keypads
char keyMap[ROWS][COLS] = {   //define the key value of keyboard
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {A8, A9, A10, A11};    //Row pinouts of the keypad
byte colPins[COLS] = {A12, A13, A14, A15};  //Column pinouts of the keypad
Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS);

//wire up ultrasonic sensor
#define EchoPin  23  //ECHO to D23
#define TrigPin  22  //TRIG to D22
#define buzzer  49   //buzzer pin to D49
#define RES     A3   //potentiometer pin to A3
#define photos  A4   //photoresistance pin to A4
#define PIR     47   //PIR pin to 47
#define MQ2_A   A0
#define MQ2_D   A1   //treat analog ports as digital ports
#define waterpin   A2
//wire up line tracking sensor
#define L_pin  50
#define M_pin  51
#define R_pin  52
#define LED    13   //led pin to D13
#define button 2    //button pin to D2

#define RGB_R  3    //connect RGB_R to D3
#define RGB_B  4    //interface RGB_B with D4
#define RGB_G  5    //interface RGB_G with D5

//define the pins of motor A, B, C and D
const int MA1 = 35;
const int MA2 = 34;
const int PWMA = 12;

const int MB1 = 33;
const int MB2 = 32;
const int PWMB = 11;

const int MC1 = 28;
const int MC2 = 29;
const int PWMC = 9;

const int MD1 = 30;
const int MD2 = 31;
const int PWMD = 10;

volatile int speeds = 150;  //define the speed variable speeds
volatile int distance;
String password1 = "0000";   //define the four bits initial password of door
String password2 = "1111";   //define the four bits initial password of trunk
String tempPassword = "";
int k = 5;
String servo_door;                  //set variable string servo_door
volatile int servo_door_angle;      //set variable servo_door_angle
String servo_trunk;                 //set variable string servo_trunk
volatile int servo_trunk_angle;     //set variable servo_trunk_angle
String servo_skylight;              //set variable string servo_trunk
volatile int servo_skylight_angle;  //set variable servo_skylight_angle
String R;              //set variable string R
volatile int value_R;  //set variable value_R
String G;              //set variable string G
volatile int value_G;  //set variable value_G
String B;              //set variable string B
volatile int value_B;  //set variable value_B
char ble_val;            //set variable  ble_val
volatile int light;      //set variable light
volatile int gas;        //set variable gas
volatile int water;      //set variable water
volatile int infrar;     //set variable infrar
int color_num = 0;
int length;

#define D0 -1
#define D1 262
#define D2 293
#define D3 329
#define D4 349
#define D5 392
#define D6 440
#define D7 494
#define M1 523
#define M2 586
#define M3 658
#define M4 697
#define M5 783
#define M6 879
#define M7 987
#define H1 1045
#define H2 1171
#define H3 1316
#define H4 1393
#define H5 1563
#define H6 1755
#define H7 1971
//list out all D frequency
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625

//list out all beats 
int tune[] =       //list out all frequency
{
  M3, M3, M4, M5,
  M5, M4, M3, M2,
  M1, M1, M2, M3,
  M3, M2, M2,
  M3, M3, M4, M5,
  M5, M4, M3, M2,
  M1, M1, M2, M3,
  M2, M1, M1,
  M2, M2, M3, M1,
  M2, M3, M4, M3, M1,
  M2, M3, M4, M3, M2,
  M1, M2, D5, D0,
  M3, M3, M4, M5,
  M5, M4, M3, M4, M2,
  M1, M1, M2, M3,
  M2, M1, M1
};
float durt[] =      //list out all beats
{
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1 + 0.5, 0.5, 1 + 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1 + 0.5, 0.5, 1 + 1,
  1, 1, 1, 1,
  1, 0.5, 0.5, 1, 1,
  1, 0.5, 0.5, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 0.5, 0.5,
  1, 1, 1, 1,
  1 + 0.5, 0.5, 1 + 1,
};

void setup() {
  Serial.begin(9600);   //serial monitor
  Serial1.begin(9600);  //Bluetooth
  rgb_2812.begin();     //Startrgb2818
  rgb_2812.setBrightness(100);   //initialize 100(0~255)
  rgb_2812.show();      //set NeoPixels to "off" state
  pinMode(door_servo, OUTPUT);    //set the pin of servo of door to OUTPUT
  pinMode(trunk_servo, OUTPUT);   //set the pin of servo of trunk to OUTPUT
  pinMode(skylight_servo, OUTPUT);//Set the pin of servo of sunproof to OUTPUT

  pinMode(buzzer, OUTPUT);    //Set buzzer as an output
  pinMode(EchoPin, INPUT);    //set pin ECHO to INPUT
  pinMode(TrigPin, OUTPUT);   //set pin TRIG to OUTPUT
  //pinMode(MQ2_D, INPUT);

  pinMode(button, INPUT);// initialize digital pin button as an input.
  attachInterrupt(digitalPinToInterrupt(button), doorbell, FALLING);  //external interrupt 0, falling edge triggers

  pinMode(L_pin, INPUT);      //set the pins of line tracking sensor to INPUT
  pinMode(M_pin, INPUT);
  pinMode(R_pin, INPUT);

  pinMode(LED, OUTPUT);       //LED pin as an OUTPUT

  //set the ports of motor to OUTPUT
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);

  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);

  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);

  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  //initialize LCD1602
  lcd.init();
  lcd.backlight();

  length = sizeof(tune) / sizeof(tune[0]);  //calculate the length
  // Print a mecountage to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Please enter: ");
  lcd.setCursor(0, 1);
  lcd.print("pass>");
  servopulse(skylight_servo, 180);  //open sunroof
}

void loop() {
  auto_sensor();                        //auto detection
  if (Serial1.available() > 0)          // serial reads the characters
  {
    ble_val = Serial1.read();           //set the character read by serial port to val
    Serial.println(ble_val);            //serial port display, used to modulate
    pwm_control();                      //PWM display

    //for not looping the program
    if (ble_val == 'o') {          //receive 'o'，switch color
      color_num++;
      showColor();
    }
    else if (ble_val == 'p') {     //receive 'p'，switch color
      color_num--;
      showColor();
    }
    else if (ble_val == 'q') {
      closeColor();                //receive 'q'，turn off 2812
    }

  }
  switch (ble_val) {

    case 'F' :  advance();   break;   //receive ‘F’, go forward

    case 'B' :  back();      break;   //receive ‘B’, go back

    case 'L' :  turnleft();  break;   //receive ‘L’, turn left

    case 'R' :  turnright(); break;   //receive ‘R’, turn right

    case 'S' :  Stop();      break;   //receive ‘S’, stop

    case 'Z':  speeds_a();   break;   //receive ‘Z’, motor speeds up

    case 'X':  speeds_d();   break;   //receive ‘X’, motor speeds down

    case 'h' :  avoid();     break;   //receive ‘h’, enter the obstacle avoidance mode

    case 'i' :  follow();    break;   //receive ‘i’, enter the following mode

    case 'j' :  track();     break;   //receive ‘j’, enter the line tracking mode

    case 'A':                     //if ble_val is 'A'，loop program
      digitalWrite(LED, HIGH);    //set digital 13 to high level，LED on
      break;                      //exit loop

    case 'H':                     //if ble_val is 'H'，loop program
      digitalWrite(LED, LOW);     //set digital 13 to low level，LED off
      break;                      //exit loop

    case 'm':                     //if ble_val is 'm'，loop program
      rainbow(10);                //2812 shows rainbow color
      break;                      //exit loop

    case 'G':                     //if ble_val is 'G'，loop program
      closeColor();               //turn off rainbow color function
      break;                      //exit loop

    case 'J':                     //if ble_val is 'J'，loop program
      music();                    //play music
      break;                      //exit loop

    case 'y':                     //if ble_val is 'y'，loop program
      Serial1.println(light);     //wrap and output the value of variable light
      break;                      //exit loop

    case 'k':                     //if ble_val is 'k'，loop program
      Serial1.println(gas);       //wrap and output the value of variable gas
      break;                      //exit loop

    case 't':                     //if ble_val is 't'，loop program
      Serial1.println(water);     //wrap and output the value of variable water
      break;                      //exit loop

    case 'l':                     //if ble_val is 'l'，loop program
      Serial1.println(DHT.temperature);   //wrap and output the value of variable soil
      break;                      //exit loop

    case 'w':                     //if ble_val is‘w’，loop program
      Serial1.println(DHT.humidity);      //wrap and output the value of variable soil
      break;                      //exit loop

    case 'W':                     //if ble_val is 'W'，loop program
      servopulse(door_servo, 10);       //open the door
      break;                      //exit loop

    case 'M':                     //if ble_val is 'M'，loop program
      servopulse(door_servo, 86);       //close the door
      break;                      //exit loop

    case 'U':                     //if ble_val is 'U'，loop program
      servopulse(skylight_servo, 180);  //open sun roof
      break;                      //exit loop

    case '9':                     //if ble_val is '9'，loop program
      servopulse(skylight_servo, 0);     //close sunroof
      break;                      //exit loop

    case 'P':                     //if ble_val is 'P'，loop program
      servopulse(trunk_servo, 120);      //turn on trunk
      break;                      //exit loop

    case '8':                     //if ble_val is '8'，loop program
      servopulse(trunk_servo, 0);      //turn off trunk
      break;                      //exit loop

    case '*':                              //if val is ‘w’，loop program
      if (infrar == 1) {
        Serial1.println("somebody!");      //linefeed “somebody!”
      } else {
        Serial1.println("nobody");         //linefeed and output “nobody”
      }
      break;                               //exit loop

    case  'V':  set_RGBColor(0, 255, 255); break;   //receive 'V' and show red color
    case  'n':  set_RGBColor(255, 0, 255); break;   //receive 'n' and show green color
    case  'Q':  set_RGBColor(255, 255, 0); break;   //receive 'Q' and show blue color
    case  'Y':  set_RGBColor(255, 255, 255); break;   //receive 'Y',turn off

    case  'a':  set_RGBColor(0, 255, 255); break;   //receive 'a'and show red color
    case  'b':  set_RGBColor(0, 90, 255);  break;   //receive 'b' and show orange color
    case  'c':  set_RGBColor(0, 0, 255);   break;   //receive 'c' and show yellow color
    case  'd':  set_RGBColor(255, 0, 255); break;   //receive 'd' and show green color
    case  'e':  set_RGBColor(255, 0, 0);   break;   //receive 'e' and show cyan color
    case  'f':  set_RGBColor(255, 255, 0); break;   //receive 'f' and show blue color
    case  'g':  set_RGBColor(95, 223, 15); break;   //receive 'g' and show purple color

    case  '1':  tone(buzzer, D1);  break;   //receive '1' and emit DO
    case  '2':  tone(buzzer, D2);  break;   //receive '2' and emit Re
    case  '3':  tone(buzzer, D3);  break;   //receive '3' and emit Mi
    case  '4':  tone(buzzer, D4);  break;   //receive '4' and emit Fa
    case  '5':  tone(buzzer, D5);  break;   //receive '5' and emit So
    case  '6':  tone(buzzer, D6);  break;   //receive '6' and emit La
    case  '7':  tone(buzzer, D7);  break;   //receive '7' and emit Si
    case  '0':  noTone(buzzer);    break;   //receive ‘0’ and stop emitting sound
    default : break;
  }

}

void auto_sensor() {
  infrar = digitalRead(PIR);      //set the digital value of digital port PIR to infrar
  gas = analogRead(MQ2_A);        //set the analog value of MQ2 port to gas
  if (gas > 700) {                //if variable ga is more than 700
    set_RGBColor(0, 255, 255);
    while (1)
    {
      Serial1.println("danger");  //linefeed and output "danger" 
      tone(buzzer, 440, 200);
      delay(300);

      tone(buzzer, 440, 200);
      delay(500);
      gas = analogRead(MQ2_A);    //set the analog value of MQ2_A to gas
      if (gas < 100)              //if variable gas is less than 100
      {
        set_RGBColor(255, 255, 255);
        break;                    //exit loop
      }
    }
  }

  light = analogRead(photos);     //set the analog value of photos to light
  if (light < 5 && ble_val != 'H')//if varible light is less than 5 and not turning off light by hand
  {
    digitalWrite(LED, HIGH);      //turn on light
  } else {
    if (ble_val != 'A' ) {        //not turning on light by hand
      digitalWrite(LED, LOW);     //turn off light
    }
  }

  water = analogRead(waterpin);   //set the analog vlaue of waterpin to variable water
  if (water > 800)                //if variable water is more than 800
  {
    set_RGBColor(255, 255, 0);
    while (1)
      //loop program
    {
      Serial1.println("rain");    //linefeed and output "rain" 
      servopulse(skylight_servo, 0);    //close sunroof
      water = analogRead(waterpin);    //set the analog vlaue of waterpin to variable water
      if (water < 30)                //if variable water is less than 30
      {
        set_RGBColor(255, 255, 255);
        break;                    //exit loop program
      }
    }

  } /*else {                        //otherwise
    if (ble_val != 'v' && ble_val != '9')   //if val is not equivalent to 'v'or '9', which means not turning off by hand 
    {
      servopulse(skylight_servo, 180);  //open sunroof
    }
  }*/
  
  int chk;
  chk = DHT.read(DHT11_PIN);      // READ DATA
  switch (chk) {
    case DHTLIB_OK:
      break;
    case DHTLIB_ERROR_CHECKSUM:   //Check and error return
      break;
    case DHTLIB_ERROR_TIMEOUT:    //timeout error return
      break;
    default:
      break;
  }
  if (DHT.humidity > 90 || DHT.temperature > 30)    //if temperature or humidity is too high
  {
    set_RGBColor(0, 255, 255);
    while (1) //loop program

    {
      // READ DATA
      chk = DHT.read(DHT11_PIN);
      switch (chk) {
        case DHTLIB_OK:
          break;
        case DHTLIB_ERROR_CHECKSUM:                 //Check and error return
          break;
        case DHTLIB_ERROR_TIMEOUT:                  //timeout error return
          break;
        default:
          break;
      }
      if (DHT.temperature > 30) {
        tone(buzzer, 2000, 100);
        delay(200);
        Serial1.println("hyperthermal!");           //linefeed and output "hyperthermal"
      }
      else if (DHT.humidity > 90) {
        tone(buzzer, 2000, 100);
        delay(200);
        Serial1.println("High humidity!");          //linefeed and output "High humidity"
      }
      if (DHT.humidity <= 90 && DHT.temperature <= 30)  //if temperature or humidity is less than or equalent to threshold
      {
        set_RGBColor(255, 255, 255);
        break;                                      //exit program loop
      }
    }

  }
  enter();                                        //run password subroutine
}

void enter() {                             //Input subprogram
  keyprecounted = myKeypad.getKey();       //Obtain key value
  if (keyprecounted != NO_KEY) {           //if key value is a number
    if (keyprecounted == '0' || keyprecounted == '1' || keyprecounted == '2' || keyprecounted == '3' ||
        keyprecounted == '4' || keyprecounted == '5' || keyprecounted == '6' || keyprecounted == '7' ||
        keyprecounted == '8' || keyprecounted == '9' ) {
      tempPassword += keyprecounted;    //save variable tempPassword
      tone(buzzer, 1000, 100);          //the sound of button
      lcd.setCursor(k, 1);
      lcd.print("*");                   //hide password
      k++;                              //display on next bit 
    }
  }
  if (k > 9) {                          //if k>9 and password exceeds four digits
    tempPassword = "";                  //clear cached password
    k = 5;                              //initialize value k
    lcd.setCursor(0, 1);                //initialize display interface
    lcd.print("pass>           ");
  }
  if ( keyprecounted == '*') {          //press * key
    k = 5;                              //initialize value k
    if ( tempPassword == password1 ) {   //if password is correct

      //LCD shows "open!" at the first character of the second row
      lcd.setCursor(0, 1);
      lcd.print("open!          ");   
      servopulse(door_servo, 10);       //open the door
      tempPassword = "";                //clear cached password
      delay(2000);                      //wait for 3s
      lcd.setCursor(0, 1);              //initialize display interface
      lcd.print("pass>           ");
    }else if ( tempPassword == password2 ) {   //if password is correct

      //LCD shows "open!" at the first character of the second row
      lcd.setCursor(0, 1);
      lcd.print("open!          ");   
      servopulse(trunk_servo, 120);     //open trunk
      tempPassword = "";                //clear cached password
      delay(2000);                      //wait for 3s
      lcd.setCursor(0, 1);              //initialize display interface
      lcd.print("pass>           ");
    }
    else {                              //if password is wrong
      lcd.setCursor(0, 1);              //prompt error
      lcd.print("Wrong! Try Again");
      tempPassword = "";                //clear cached password
      delay(2000);                      //wait for 2s
      lcd.setCursor(0, 1);              //initialize display interface
      lcd.print("pass>           ");
    }
  }
}

//PWM and angle control of servo
void pwm_control() {
  switch (ble_val)
  {
    case 'u':                                   //when ble_val is 'u', loop program
      servo_door = Serial1.readStringUntil('#');
      servo_door_angle = String(servo_door).toInt();
      servopulse(door_servo, servo_door_angle);       //set the servo of door to servo_door_angle
      break;                                    //exit loop
    case 'v':                                   //when ble_val is 'v', loop program
      servo_skylight = Serial1.readStringUntil('#');
      servo_skylight_angle = String(servo_skylight).toInt();
      servopulse(skylight_servo, servo_skylight_angle);     //set the servo angle of sunroof to servo_skylight_angle
      break;//exit loop
    case 's':                                   //when ble_val is 's', loop program
      servo_trunk = Serial1.readStringUntil('#');
      servo_trunk_angle = String(servo_trunk).toInt();
      servopulse(trunk_servo, servo_trunk_angle);     //set the servo angle of trunk to servo_trunk_angle
      break;                                    //exit loop

    case 'x':                                   //when ble_val is 'x', loop program
      R = Serial1.readStringUntil('#');
      value_R = String(R).toInt();
      value_R = map(value_R, 0, 255, 255, 0);   //map the  value_R
      analogWrite(RGB_R, value_R);              //set the PWM value of digital 3 to value_R
      break;                                    //exit loop
    case 'D':                                   //when ble_val is 'D', loop program
      G = Serial1.readStringUntil('#');
      value_G = String(G).toInt();
      value_G = map(value_G, 0, 255, 255, 0);   //map the value_G 
      analogWrite(RGB_G, value_G);              //set the PWM value of digital 5 to value_G
      break;                                    //exit loop
    case 'E':                                   //when ble_val is 'E', loop program
      B = Serial1.readStringUntil('#');
      value_B = String(B).toInt();
      value_B = map(value_B, 0, 255, 255, 0);   //map the value_B
      analogWrite(RGB_B, value_B);              //set the PWM value of digital 4 to value_B
      break;                                    //exit loop
  }
}

void servopulse(int pin, int myangle) {             //pulse function
  int pulsewidth = map(myangle, 0, 180, 500, 2500); //map the angel to pulsewidth
  for (int i = 0; i < 5; i++) {                     //output pulse 
    digitalWrite(pin, HIGH);                        //set the level of servo port to HIGH
    delayMicroseconds(pulsewidth);                  //Delay the tine of pulsewidth 
    digitalWrite(pin, LOW);                         //set the level of servo port to LOW
    delay(20 - pulsewidth / 1000);
  }
}

void music()   //play the "Ode to Joy" song
{
  for (int x = 0; x < length; x++)
  {
    tone(buzzer, tune[x]);
    delay(400 * durt[x]);
    noTone(buzzer);
    ble_val = Serial1.read();
    if (ble_val == 'I') {             //receive‘J’and exit loop，stop playing music
      noTone(buzzer);
      break;
    }
  }
}

void set_RGBColor(int red, int green, int blue) {   //set the color of RGB module
  analogWrite(RGB_R, red);
  analogWrite(RGB_G, green);
  analogWrite(RGB_B, blue);
}

int get_distance() {                  //ultrasonic ranging
  int dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);        //send at least 10us high level to trigger
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 58;  //calculate distance
  delay(10);
  return dis;
}

void follow() {                       //ultrasonic following
  while (1) {
    distance = get_distance();
    Serial.println(distance);
    if (distance <= 8) {
      back();
    }
    else if (distance > 8 && distance <= 15) {
      Stop();
    }
    else if (distance > 15 && distance <= 35) {
      advance();
    }
    else {
      Stop();
    }
    ble_val = Serial1.read();
    if (ble_val == 'S') {             //receive‘S’and exit loop，car stops
      Stop();
      break;
    }
  }

}

void avoid() {                        //ultrasonic avoiding
  while (1) {
    distance = get_distance();        //set distance to variable distance
    Serial.println(distance);
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
    ble_val = Serial1.read();
    if (ble_val == 'S') {             //receive ‘S’and exit loop，car stops
      Stop();
      break;
    }
  }

}

void track() {
  int L_val;
  int M_val;
  int R_val;
  while (1) {
    L_val = digitalRead(L_pin);            //read the value of left sensor
    M_val = digitalRead(M_pin);            //read the value of middle sensor
    R_val = digitalRead(R_pin);            //read the value of right sensor
    if (M_val == 1) {                      //the middle sensor detects black lines
      if (L_val == 1 && R_val == 0) {      //if only left sensor detects black lines, turn left
        turnleft();
      }
      else if (L_val == 0 && R_val == 1) { //if only right sensor detects black lines, turn right
        turnright();
      }
      else {                               //go forward
        advance();
      }
    }
    else {                                 //the middle sensor doesn't detect black lines
      if (L_val == 1 && R_val == 0) {      //if only left sensor detects black lines, turn left
        turnleft();
      }
      else if (L_val == 0 && R_val == 1) { //if only right sensor detects black lines, turn right
        turnright();
      }
      else {                               //stop
        Stop();
      }
    }
    ble_val = Serial1.read();
    if (ble_val == 'S') {                  //receive ‘S’ and exit loop，car stops
      Stop();
      break;
    }
  }

}

void advance() {    //go forward
  //Motor A rotates clockwise
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWMA, speeds);
  //Motor B rotates clockwise
  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
  analogWrite(PWMB, speeds);
  //Motor C rotates clockwise
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(PWMC, speeds);
  //Motor D rotates clockwise
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, HIGH);
  analogWrite(PWMD, speeds);
}

void back() {   //go back
  //Motor A rotates anticlockwise
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  analogWrite(PWMA, speeds);
  //Motor B rotates anticlockwise
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWMB, speeds);

  //Motor C rotates anticlockwise
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(PWMC, speeds);

  //Motor D rotates anticlockwise
  digitalWrite(MD1, HIGH);
  digitalWrite(MD2, LOW);
  analogWrite(PWMD, speeds);

}

void turnleft() {   //turn left
  //Motor A rotates clockwise
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWMA, speeds);
  //Motor B rotates anticlockwise
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWMB, speeds);
  //Motor C rotates anticlockwise
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(PWMC, speeds);
  //Motor D rotates clockwise
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, HIGH);
  analogWrite(PWMD, speeds);
}

void turnright() {    //turn right
  //Motor A rotates anticlockwise
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  analogWrite(PWMA, speeds);
  //Motor B rotates clockwise
  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
  analogWrite(PWMB, speeds);
  //Motor C rotates clockwise
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(PWMC, speeds);
  //Motor D rotates anticlockwise
  digitalWrite(MD1, HIGH);
  digitalWrite(MD2, LOW);
  analogWrite(PWMD, speeds);
}

void turnleft1() {   //Differential left-turning
  //Motor A rotates clockwise
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWMA, 180);

  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);

  //Motor D rotates clockwise
  digitalWrite(MD1, LOW);
  digitalWrite(MD2, HIGH);
  analogWrite(PWMD, 180);
}

void turnright1() {    //Differential right-turning
  analogWrite(PWMA, 0);

  //Motor B rotates clockwise
  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
  analogWrite(PWMB, 180);
  //Motor C rotates clockwise
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(PWMC, 180);

  analogWrite(PWMD, 0);
}

void Stop() {   //stop
  //set the speed of four motors to 0
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);
  analogWrite(PWMD, 0);
}

void speeds_a() {                  //speed-up function
  while (1) {
    Serial1.println(speeds);       //Show speed
    if (speeds < 255) {            //increase to 255
      speeds++;
      delay(15);                   //adjsut the change of speed-up
    }
    ble_val = Serial1.read();
    if (ble_val == 'S')break;      //receive ‘S’and stop speeding up
  }
}

void speeds_d() {                  //Deceleration function
  while (1) {
    Serial1.println(speeds);       //Show speed
    if (speeds > 0) {              //decrease to 0
      speeds--;
      delay(15);                   // adjsut the change of speed-down
    }
    ble_val = Serial1.read();
    if (ble_val == 'S')break;      //receive ‘S’and stop speeding down
  }
}

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return rgb_2812.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return rgb_2812.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return rgb_2812.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < 10; i++) {
      rgb_2812.setPixelColor(i, Wheel((i + j) & 255));
    }
    rgb_2812.show();
    delay(wait);
  }
}

void showColor() {
  //  Serial.print("color num:"); //used to serial modulation
  //  Serial.println(color_num);
  //  only set seven colors, you could add the color yourself
  if (color_num > 6)color_num = 0;
  if (color_num < 0)color_num = 6;
  switch (color_num) {
    case  0:
      for (int i = 0; i <= 9; i++) {
        rgb_2812.setPixelColor(i, 255, 0, 0);  //Number i LED shows red color
        rgb_2812.show();                       //show
      }
      break;
    case  1:
      for (int i = 0; i <= 9; i++) {
        rgb_2812.setPixelColor(i, 255, 80, 0); //Number i LED shows orange color
        rgb_2812.show();                       //show
      }
      break;
    case  2:
      for (int i = 0; i <= 9; i++) {
        rgb_2812.setPixelColor(i, 255, 255, 0); //Number i LED shows yellow color
        rgb_2812.show();                        //show
      }
      break;
    case  3:
      for (int i = 0; i <= 9; i++) {
        rgb_2812.setPixelColor(i, 0, 255, 0);   //Number i LED shows green color
        rgb_2812.show();                        //show
      }
      break;
    case  4:
      for (int i = 0; i <= 9; i++) {
        rgb_2812.setPixelColor(i, 0, 0, 255);   //Number i LED shows blue color
        rgb_2812.show();                        //show
      }
      break;
    case  5:
      for (int i = 0; i <= 9; i++) {
        rgb_2812.setPixelColor(i, 0, 255, 255); //Number i LED shows indigo color
        rgb_2812.show();                        //show
      }
      break;
    case  6:
      for (int i = 0; i <= 9; i++) {
        rgb_2812.setPixelColor(i, 160, 32, 240);//Number i LED shows purple color
        rgb_2812.show();                        //show
      }
      break;
    default : break;
  }
}

void closeColor() {                            //turn off 2818 LEDs
  for (int i = 0; i < 10; i++) {
    rgb_2812.setPixelColor(i, 0, 0, 0);        //turn off number i LED 
    rgb_2812.show();                           //execute display
  }
}

void doorbell() { //doorbell
  delay(10);  //Delay jitter elimination
  if (!digitalRead(button)) {
    for (int i = 0; i < 300; i++) // output a sound with frequency
    {
      digitalWrite(buzzer, HIGH);
      delayMicroseconds(520);//delay in 520us
      digitalWrite(buzzer, LOW);
      delayMicroseconds(520);//delay in 520us
    }
    for (int i = 0; i < 180; i++) // output another sound with frequency
    {
      digitalWrite(buzzer, HIGH);
      delayMicroseconds(1330);//delay in 1330us
      digitalWrite(buzzer, LOW);
      delayMicroseconds(1330);//delay in 1330us
    }
  }
}
