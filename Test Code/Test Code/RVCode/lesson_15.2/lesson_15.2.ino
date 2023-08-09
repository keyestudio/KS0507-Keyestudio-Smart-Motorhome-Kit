/*
  keyestudio smart RV
  lesson 15.2
  Ultrasonic sensor
  http://www.keyestudio.com
*/
//Ultrasonic Sensor
#define EchoPin  23  //ECHO to D23
#define TrigPin  22  //TRIG to D22
const int LED = 13;  //led pin to D13
volatile int distance;
void setup() {
  Serial.begin(9600);
  pinMode(EchoPin, INPUT);  //set pin ECHO to INPUT
  pinMode(TrigPin, OUTPUT);  //set pin TRIG to OUTPUT
  pinMode(LED, OUTPUT);
}

void loop () {
  distance = get_distance();  //set distance to variable distance
  Serial.println(distance);
  if (distance < 10) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}

int get_distance() {  //detect distance by ultrasonic sensor
  int dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);  //trigger TRIG at least 10us high level
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 58;   //calculate distance
  delay(10);  //delay in 50ms
  return dis;
}
