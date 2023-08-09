/*
  keyestudio smart RV
  lesson 16.1
  I2C 1602
  http://www.keyestudio.com
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // includes the LiquidCrystal_I2C Library 
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();  //set backlight
  lcd.setCursor(0,0); //set cursor at the first row and first column
  lcd.print("Hello, World!"); //display "Hello, World!"
  lcd.setCursor(0,1); //at the second row and first column
  lcd.print("Hello, Keyes!"); //show "Hello, Keyes!"
}

void loop () {
  
}
