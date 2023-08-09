/*
  keyestudio smart RV 
  lesson 11.1
  water sensor
  http://www.keyestudio.com
*/
#define waterpin A5 //water sensor pin to A5
volatile int water = 0;

void setup() {
  Serial.begin(9600);

}

void loop () {
  water = analogRead(waterpin);  //read the analog value of water sensor
  Serial.println(water);
  delay(100);
}
