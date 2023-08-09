/*
  keyestudio smart RV
  lesson 19.2
  bluetooth
  http://www.keyestudio.com
*/
char ble_val;   //set variable to ble_val
#define LED    13    //led pin to D13
void setup() {
  Serial1.begin(9600);  //set Bluetooth baud rate to 9600
  pinMode(LED, OUTPUT); //set the pin of LED to OUTPUT

}

void loop () {
  if (Serial1.available() > 0) //determine if there is data in the buffer of Bluetooth serial port
  {
    ble_val = Serial1.read();  //read the data saved in the buffer of Bluetooth serial port
    if (ble_val == 'A') {
      digitalWrite(LED, HIGH);
    }
    else if (ble_val == 'H') {
      digitalWrite(LED, LOW);
    }
  }
}
