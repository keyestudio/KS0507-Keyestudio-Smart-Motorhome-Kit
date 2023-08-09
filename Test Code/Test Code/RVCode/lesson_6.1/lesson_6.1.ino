/*
  keyestudio 智能房车
  lesson 6.1
  Keypad
  http://www.keyestudio.com
*/

#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keypressed;
//define the cymbols on the buttons of the keypads
char keyMap[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {A8, A9, A10,A11}; //Row pinouts of the keypad
byte colPins[COLS] = {A12, A13, A14, A15}; //Column pinouts of the keypad
Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600); //设置波特率为9600
}

void loop ()
{
  keypressed = myKeypad.getKey();  //读取键值
  if (keypressed != NO_KEY) { //读取到键值
    Serial.print("key:");
    Serial.println(keypressed);   //打印键值
  }
}
