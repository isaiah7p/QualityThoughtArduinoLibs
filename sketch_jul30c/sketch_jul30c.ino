#include <Arduino.h>
#include <math.h>
#include <Wire.h>
#include "MAX30100.h"

MAX30100 *pulseOxymeter;
 //LiquidCrystal lcd(8,9,4,5,6,7)

int mode = 0;

void setup() {
  Wire.begin();
//  lcd.begin(16,2);
//  lcd.print("Up for SaO2")
//  lcd.setCurson(0,2);
//  lcd.println("Pulse oxymeter test!")
Serial.begin(9600);
  pulseOxymeter = new MAX30100( DEFAULT_OPERATING_MODE, DEFAULT_SAMPLING_RATE, DEFAULT_LED_PULSE_WIDTH, DEFAULT_IR_LED_CURRENT, true, false);
  pinMode(2, OUTPUT);
  Serial.println("Heart Beat ::: ");
}

void loop() {
  pulseoxymeter_t result = pulseOxymeter->update();

  if ((analogRead(0)>130) && (analogRead(0)<160)) {
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print( "SaO2: " );
    mode = 1;

  } else if ((analogRead(0)>130) && (analogRead(0)<160)) {
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print( "BPM: " );
    mode = 2;

  if (result.pulseDetected == true)
  {
    if (mode == 1) {
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print( "SaO2: ");
//      lcd.print( result.SaO2 );
//      lcd.print( "%" );
Serial.println(result.SaO2);

    } else if (mode == 2) {
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print( "BPM: ");
//      lcd.print(result.heartBPM);
Serial.println(result.heartBPM);
    }

  }

  delay(10);
  digitalWrite( 2, !digitalRead(2) );

}
