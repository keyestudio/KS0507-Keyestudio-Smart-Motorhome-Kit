/*
  keyestudio smart RV
  lesson 3.1
  button
  http://www.keyestudio.com
*/
#define button 2 //Define the pin of LED as D12
volatile int buttonState;  //The output level state of button module
void setup()
{
  Serial.begin(9600);//set baud rate to 9600
  pinMode(button, INPUT);// initialize digital pin button as an input.
}
void loop () {
  buttonState = digitalRead(button);
  Serial.println(buttonState);  //auto wrap and output the digital signals from digital 2
  delay(100);//delay in 100ms
}
