// http://davidhoulding.blogspot.in/2014/06/gps-location-sensing-with-itead-gps.html

#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#include "TinyGPS.h"

TinyGPS gps;

int unoRxPin = 6; // connected to Tx pin of the GPS
int unoTxPin = 7; // connected to Rx pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C
//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
int backLight = 13;    // pin 13 will control the backlight

long startMillis;
long secondsToFirstLocation = 0;
void setup()
{ Serial.begin(9600);
  ss.begin(115200);

  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
   lcd.begin(16, 2); // columns, rows.  use 16,2 for a 16x2 LCD, etc.
   lcd.clear();  // start with a blank screen
  Serial.print("In Setup of GPS Module ");
  startMillis = millis();
}

void loop()
{
  bool newData = false;
  unsigned long chars = 0;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      int c = ss.read();
      ++chars;
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    // we have a location fix so output the lat / long and time to acquire
    if (secondsToFirstLocation == 0) {
      secondsToFirstLocation = (millis() - startMillis) / 1000;
    }

    lcd.clear();  // start with a blank screen

    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    lcd.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
    lcd.print("La:");
    lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);

    lcd.setCursor(0, 0);
    lcd.print("Lo:");
    lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Acquire Time=");
    lcd.print(secondsToFirstLocation);
    lcd.print("s");

    Serial.print("GPS Coordinates : Lat ");Serial.println(flat,6);
    Serial.print("GPS Coordinates : long ");Serial.println(flon,6);
    Serial.print("GPS time taken to SatComm :  ");Serial.println(secondsToFirstLocation);Serial.print("s");
    //speed = ;
    float fkmph = gps.f_speed_kmph();
    Serial.println("GPS Speed "); Serial.print(fkmph);Serial.print("kmph");
    
  }

  if (chars == 0) {
    // if you haven't got any chars then likely a wiring issue
    lcd.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
    lcd.print("No GPS: check wiring");
   Serial.println("No GPS: check wiring ");
  }
  else if (secondsToFirstLocation == 0) {
    // if you have received some chars but not yet got a fix then indicate still searching and elapsed time
   //lcd.clear();  // start with a blank screen
    
    long seconds = (millis() - startMillis) / 1000;

    lcd.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
    lcd.print("Searching ");
  Serial.println("Searching");
 
    for (int i = 0; i < seconds % 4; ++i) {
      Serial.println(".");
      lcd.print(".");
    }
  Serial.println("Elapsed time:");
  Serial.println(seconds);
  Serial.println("s");
    lcd.setCursor(0, 1);
    lcd.print("Elapsed time:");
    lcd.print(seconds);
    lcd.print("s");
  }
    
     
}
