/*
  keyestudio smart RV
  lesson 11.2
  water sensor
  http://www.keyestudio.com
*/
#define waterpin A5 //define the pin of water sensor as A5
#define buzzer   49 //define the pin of buzzer as D49
volatile int water = 0;
void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);//set buzzer to OUTPUT
}

void loop () {
  water = analogRead(waterpin);  //read the analog value of water sensor
  Serial.println(water);
  if (water > 300) {  //when the analog value is more than 300
    tone(buzzer,2000); //buzzer emits the sound with 2000Hz 
  }
  else {  //when the analog value is less than 300
    noTone(buzzer); //turn off buzzer
  }
  
}
