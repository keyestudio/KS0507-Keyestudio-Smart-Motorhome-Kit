/*
  keyestudio smart RV
  lesson 5.1
  PIR
  http://www.keyestudio.com
*/

//PIR Motion Sensor
#define PIR  47   //PIR pin to D47  

void setup()
{
  Serial.begin(9600); //set baud rate to 9600
  pinMode(PIR, INPUT); //set the pin of PIR motion sensor to INPUT

}
void loop ()
{
  int val = digitalRead(PIR); //set the variable val to the value read
  Serial.println(val);
  delay(100); //delay in 100ms

}
