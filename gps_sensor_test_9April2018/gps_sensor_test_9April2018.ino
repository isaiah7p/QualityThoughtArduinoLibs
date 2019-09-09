#include <SoftwareSerial.h>
#include "TinyGPS.h"
TinyGPS gps;
//
int unoRxPin = 4; // connected to TX pin of the GPS
int unoTxPin = 5; // connected to RX pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);


int backLight = 13;    // pin 13 will control the backlight
//
long startMillis;
long secondsToFirstLocation = 0;
float gpsSpeed ;
float flat = 0;
float flon = 0;

    bool newData = false;
    unsigned long chars = 0;
    unsigned short sentences, failed;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("set up method .... ");
  ss.begin(9600);
  startMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  // GPS Data Aquaring
    Serial.println("loop method .... ");
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
      Serial.print("have new data available  .... ");
      // we have a location fix so output the lat / long and time to acquire
      if (secondsToFirstLocation == 0) {
        secondsToFirstLocation = (millis() - startMillis) / 1000;
      }

      // lcd2.clear();  // start with a blank screen

      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);
      gpsSpeed = gps.f_speed_kmph();

//      if (gpsSpeed >= topGPSSpeed) {
//
//        topGPSSpeed = gpsSpeed;
//
//
//      } else if (gpsSpeed >= topGPSSpeed) {
//        // do nothing
//      } else {
//        // do nothing
//      }


      // GPS Top Speed 
  //    Serial.print("Top Speed =");
  //    Serial.println(topGPSSpeed , 2);



      // lcd2.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
      Serial.print("Lat=");
      Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);

      //

      Serial.print("Long=");
      Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      Serial.print("  !!!  GPS SPeed =");
      Serial.print(gpsSpeed);

      if (chars == 0) {
        // if you haven't got any chars then likely a wiring issue
       // lcd2.setCursor(0, 2);          // set cursor to column 0, row 0 (the first row)
        Serial.print("No GPS: check wiring");
      }
      else if (secondsToFirstLocation == 0) {
        // if you have received some chars but not yet got a fix then indicate still searching and elapsed time
        //lcd2.clear();  // start with a blank screen

        long seconds = (millis() - startMillis) / 1000;

;
        for (int i = 0; i < seconds % 4; ++i) {
          Serial.print(".");
         // lcd2.print(".");
        }


      }

    }

}
