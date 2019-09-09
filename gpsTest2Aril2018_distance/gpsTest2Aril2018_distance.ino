#include <SoftwareSerial.h>
#include "TinyGPS.h"

TinyGPS gps;
//
int unoRxPin = 10; // connected to TX pin of the GPS
int unoTxPin = 11; // connected to RX pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);

float homeLat ;float homeLon ;

int startPoint = 0;

int backLight = 13;    // pin 13 will control the backlight
//
long startMillis;
long secondsToFirstLocation = 0;

float flat = 0;
float flon = 0;
float gpsSpeed = 0;

void setup() {
  Serial.begin(115200);
Serial.println("Setup");
  ss.begin(9600);

} // setup ends here

void loop() {

Serial.println("loop");
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


      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);
      gpsSpeed = gps.f_speed_kmph();



      // lcd2.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
      Serial.print("Lat=");
      Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);

      //

      Serial.print("Long=");
      Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      Serial.print("  !!!  GPS SPeed =");
      Serial.print(gpsSpeed);
      if(startPoint==0){
         homeLat =flat ; homeLon=flon ;
        }
      if (chars == 0) {
               Serial.print("No GPS: check wiring");
      }
      else if (secondsToFirstLocation == 0) {
        // if you have received some chars but not yet got a fix then indicate still searching and elapsed time

        long seconds = (millis() - startMillis) / 1000;

       for (int i = 0; i < seconds % 4; ++i) {
         // lcd2.print(".");
        }


      }
    }

   if(startPoint>0){
   float distanceSoFar =  distanceInKmBetweenEarthCoordinates(homeLat, homeLon, flat, flon);
   Serial.print("Distance Travelled From Starting Point ");
     Serial.print(distanceSoFar);
   }
   startPoint++;
}

float degreesToRadians(float degrees) {
  return degrees * PI / 180;
}

float distanceInKmBetweenEarthCoordinates(float lat1 ,float lon1 , float lat2 ,float lon2) {
  float earthRadiusKm = 6371;

  float dLat = degreesToRadians(lat2-lat1);
  float dLon = degreesToRadians(lon2-lon1);

  lat1 = degreesToRadians(lat1);
  lat2 = degreesToRadians(lat2);

  float a = sin(dLat/2) * sin(dLat/2) +
          sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
  float c = 2 * atan2(sqrt(a), sqrt(1-a)); 
  return earthRadiusKm * c;
}
