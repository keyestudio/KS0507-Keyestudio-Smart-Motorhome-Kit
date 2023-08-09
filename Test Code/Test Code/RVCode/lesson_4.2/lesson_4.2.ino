/*
  keyestudio smart RV
  lesson 4.2
  Line Track sensor
  http://www.keyestudio.com
*/
//LED pin
#define LED 13
//Line Tracking Sensor
#define L_pin  50
#define M_pin  51
#define R_pin  52
void setup()
{
  Serial.begin(9600); //set baud rate to 9600
  pinMode(LED, OUTPUT); //set LED to OUTPUT
  pinMode(L_pin, INPUT); //set the pin of line tracking sensor to INPUT
  pinMode(M_pin, INPUT);
  pinMode(R_pin, INPUT);
}
void loop ()
{
  int L_val = digitalRead(L_pin); //read the value of left sensor
  int M_val = digitalRead(M_pin); //read the value of middle sensor
  int R_val = digitalRead(R_pin); //read the value of right sensor
  Serial.print(L_val);
  Serial.print("  ");
  Serial.print(M_val);
  Serial.print("  ");
  Serial.print(R_val);
  Serial.println("  ");
  delay(100); //delay in 100ms
  if (L_val == 0 || M_val == 0 || R_val == 0) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}
