/*
  keyestudio smart RV
  lesson 15.1
  Ultrasonic sensor
  http://www.keyestudio.com
*/
//Ultrasonic Sensor
#define EchoPin  23  //ECHO to D23
#define TrigPin  22  //TRIG to D22
float dis;
void setup() {
  Serial.begin(9600);
  pinMode(EchoPin, INPUT);  // set pin ECHO to INPUT
  pinMode(TrigPin, OUTPUT);  //set pin TRIG to OUTPUT

}

void loop () {
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);  //trigger TrigPin at least 10us high level 
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 2 / 29.1;   //calculate distance
  delay(50);  //delay in 50ms
  Serial.print("distance: ");
  Serial.print(dis);
  Serial.println("cm");
}
