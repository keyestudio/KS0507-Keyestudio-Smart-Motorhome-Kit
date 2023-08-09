/*
  keyestudio smart RV
  lesson 5.2
  PIR
  http://www.keyestudio.com
*/

//PIR Motion Sensor
#define PIR  47   //PIR pin to D47  
#define LED  13   //LED pin to D13
void setup()
{
  pinMode(LED, OUTPUT); //set LED to OUTPUT
  pinMode(PIR, INPUT); //set PIR motion sensor to INPUT

}
void loop ()
{
  int val = digitalRead(PIR); //set val to the value read by sensor
  if (val == 1) {   //People is detected
    digitalWrite(LED, HIGH); //turn on LED
  }
  else {
    digitalWrite(LED, LOW); //otherwise, lED will be off
  }

}
