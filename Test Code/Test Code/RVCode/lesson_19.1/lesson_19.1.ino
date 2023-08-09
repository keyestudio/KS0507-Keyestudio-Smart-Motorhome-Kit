/*
  keyestudio smart RV
  lesson 19.1
  bluetooth
  http://www.keyestudio.com
*/
char ble_val;   //set variable ble_val

void setup() {
  Serial.begin(9600);   //set USB baud rate to 9600
  Serial1.begin(9600);  //set Bluetooth baud rate to 9600
}

void loop () {
  if (Serial1.available() > 0) // determine if there is data in the buffer of serial port
  { 
    ble_val = Serial1.read();  //read the data saved in the buffer of serial port
    Serial.println(ble_val);  //serial port prints data
  }
}
