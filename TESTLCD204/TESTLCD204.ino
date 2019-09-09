#include <Wire.h> 
// Use this library with I2C-module found on the webpage
// http://4tronix.co.uk/arduino/I2C_LCD_Module.php
#include <LiquidCrystal_I2C.h>


// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
// addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd2(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address

void setup()
{
 
 lcd2.begin(16,2); // initialize the lcd
 
 lcd2.backlight();
 lcd2.print(" HELLO SARAH ");
 //lcd2.setCursor(0, 1);
// lcd2.print("HELLO, WORLD 1!");
// lcd2.setCursor(0, 2);
// lcd2.print("HELLO, WORLD 2!");
// lcd2.setCursor(0, 3);
// lcd2.print("HELLO, WORLD 3!");
}

void loop()
{
  lcd2.clear();
 
  lcd2.setCursor(0, 0);
  lcd2.print("DustDevils Product ");
  
 // lcd2.setCursor(0 , 1);
 // lcd2.print("     :");
  
  //lcd2.print("Y Val");
  
// lcd2.setCursor(0 , 2);
//  lcd2.print("PITCH   :");
//  
//  lcd2.print("Pitch Val");
//    
// lcd2.setCursor(0 , 3);
//  lcd2.print("RADIUS  :");
//  
//  lcd2.print("rad Val");
    
    delay(500);

  
}
