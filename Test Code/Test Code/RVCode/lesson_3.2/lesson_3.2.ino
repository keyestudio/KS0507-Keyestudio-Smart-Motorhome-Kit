/*
  keyestudio smart RV
  lesson 3.2
  button
  http://www.keyestudio.com
*/
#define LED 13 //Define the pin of LED as D13
#define button 2 //Define the pin of button module as D2
volatile int buttonState;  //the state of button
void setup()
{
  Serial.begin(9600); //set baud rate to 9600
  pinMode(button, INPUT); // initialize digital pin button as an input.
  pinMode(LED, OUTPUT); // initialize digital pin LED as an output.
}
void loop ()
{
  buttonState = digitalRead(button);    //read the status of button
  if (buttonState == 0) //if the button is pressed
  {
    digitalWrite(LED, HIGH);  //Turn on LED
  }
  else
  {
    digitalWrite(LED, LOW);   //turn off LED
  }
  delay(100); //dealy in 100ms
}
