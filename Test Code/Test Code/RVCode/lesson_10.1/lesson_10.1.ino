/*
  keyestudio smart RV
  lesson 10.1
  photovaristor
  http://www.keyestudio.com
*/
#define photos  A4   //set photoresistance pin to A4
#define LED 13   //define the pin of LED as D13
volatile int value = 0;
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);// initialize digital pin LED as an output.
}

void loop () {
  value = analogRead(photos);  //read the value of photoresistor 
  Serial.println(value);
  if (value < 300) {  //when the analog vlaue is les than 300
    digitalWrite(LED, HIGH); //turn on LED
  }
  else {  //when the analog vlaue is higher than 300
    digitalWrite(LED, LOW); //turn off LED
  }
  delay(100);               //delay in 100MS
}
