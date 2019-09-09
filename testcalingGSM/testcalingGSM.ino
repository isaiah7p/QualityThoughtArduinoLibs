#include <SoftwareSerial.h>
SoftwareSerial sim800l(10, 11); //RX - TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   sim800l.begin(9600);
  // sim800l.listen();
  //   sim800l.println(F("AT"));
  //   delay(200);
//         
//            sim800l.println(F("AT+CBC"));
//           delay(200);
//
//            sim800l.println(F("AT+CSQ"));
//            delay(200);
//      
//            sim800l.println(F("AT+CMGF=1"));
//            delay(200);
            
//  sim800l.println(F("AT+CGREG"));
//  delay(200);
//  sim800l.println(F("ATD+919848477144;"));
//  delay(500);
 // Serial.println("setup");
}

void loop() {
  // put your main code here, to run repeatedly:
//sim800l.listen();
hac_llam() ;
}

void hac_llam() {
  //sim800l.listen();
  sim800l.println(F("ATD+919676867575;"));
  delay(500);
  Serial.println("Calling IN_CASE_OF_EMERGENCY_NUMBERS");
}

