#include "TinyGPS.h"
#include <SoftwareSerial.h>

TinyGPS gps;
//
int unoRxPin = 10; // connected to TX pin of the GPS
int unoTxPin = 11; // connected to RX pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);
long startMillis;
long secondsToFirstLocation = 0;
float gpsSpeed ;
float flat = 0;
float flon = 0;

// SIM Module setup
SoftwareSerial sim800l(10, 11); //RX - TX 

 
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
ss.begin(115200);
Serial.begin(115200);
//sim800l.begin(115200);

Serial.println("SetUP ");

}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println("loop "); 
    if(ss.available()){
           Serial.println(" GPS Available  ");    
      }else{
        Serial.println("  GPS Not Available  "); 
        }
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
     // Serial.print("  !!!  GPS SPeed =");
     // Serial.print(gpsSpeed);

      if (chars == 0) {
        // if you haven't got any chars then likely a wiring issue
       // lcd2.setCursor(0, 2);          // set cursor to column 0, row 0 (the first row)
        Serial.print("No GPS: check wiring");
      }
      else if (secondsToFirstLocation == 0) {
        // if you have received some chars but not yet got a fix then indicate still searching and elapsed time
        //lcd2.clear();  // start with a blank screen

        long seconds = (millis() - startMillis) / 1000;

        //lcd2.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
       // lcd2.print("Searching ");
        for (int i = 0; i < seconds % 4; ++i) {
         // lcd2.print(".");
        }

        //lcd2.setCursor(0, 1);
        //lcd2.print("Elapsed time:");
        //lcd2.print(seconds);
        //lcd2.print("s");
      }

    }

  //   Serial.println("-- SUBBU -- Phone ");

//      sim800l.println(F("AT"));
//      delay(200);
//      //Serial.println(debug());
//      sim800l.println(F("AT+CBC"));
//      delay(200);
//      //Serial.println(debug());
//
//      sim800l.println(F("AT+CSQ"));
//      delay(200);
//
//      sim800l.println(F("AT+CMGF=1"));
//      delay(200);
//      //if (res_at(debug(),"OK")){
//    //  sim800l.println(F("AT+CMGS=\"+919005532069\""));//
//      sim800l.println(F("AT+CMGS=\"+919676867575\""));//
//      delay(200);
//      // if(res_at(debug(),">")){
//      sim800l.println("Emergency Help for Test   ,pls reach him  ");
//      sim800l.print("maps.google.com/?q=");
//      sim800l.print(flat, 6);
//      sim800l.print(",");
//      sim800l.print(flon, 6);
//    //  sim800l.println(" HEALTH CARD  : 7869 7868 6778 1234");
//
//
//      //sim800l.println("maps.google.com");
//      delay(200);
//      sim800l.println();
//      delay(200);
//      sim800l.write(0x1A);
//      delay(200);

  delay(1000);


}
