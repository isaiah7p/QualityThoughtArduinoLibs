#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};
byte rowPins[ROWS] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd(0x3F,20,4);

void setup(){
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("you  pressed : ");
 //  Serial.begin(9600);
  
}

void loop(){
  char key = keypad.getKey();
  
  if (int(key) != 0){
    lcd.setCursor(16,0);
    lcd.print(key);
    //Serial.println(key);
  }
}

