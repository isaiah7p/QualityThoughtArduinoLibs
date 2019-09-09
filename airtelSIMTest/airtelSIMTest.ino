
#include "Wire.h"
#include <SoftwareSerial.h>


// SIM Module setup
SoftwareSerial sim800l(10, 11); //RX - TX

void setup()
{
  Serial.begin(115200);  //Open Serial connection at baud 9600
  Serial1.begin(9600);
  // sim800l.begin(4800);

}
void loop()
{
 
//      sim800l.listen();
//      Serial.println("-- SUBBU -- Phone ");
//
//      sim800l.println(F("AT"));
//      delay(200);
//      //Serial.println(debug());
//      sim800l.println(F("AT+CBC"));
//      delay(200);
//      //Serial.println(debug());
//Serial.println("-- debug  1");
//      sim800l.println(F("AT+CSQ"));
//      delay(200);
//Serial.println("-- debug  2");
//      sim800l.println(F("AT+CMGF=1"));
//      delay(200);
//      //if (res_at(debug(),"OK")){
//      sim800l.println(F("AT+CMGS=\"+919676867575\""));
//      Serial.println("-- debug  3");
//      delay(200);
//      // if(res_at(debug(),">")){
//      sim800l.println("Emergency Help for Subash DD ,pls reach him  ");
//Serial.println("-- debug  4");
//      sim800l.println("maps.google.com"); 
//      delay(200);
//      sim800l.println("");
//      delay(200);
//      sim800l.write(0x1A);
//      delay(200);
//      Serial.println("-- sms done ");
  //  Serial1.listen();
      Serial.println("-- Srilakshmi -- Phone ");

      Serial1.println(F("AT"));
      delay(200);
      //Serial.println(debug());
      Serial1.println(F("AT+CBC"));
      delay(200);
      //Serial.println(debug());
Serial.println("-- debug  1");
      Serial1.println(F("AT+CSQ"));
      delay(200);
      Serial.println("-- debug  2");
      Serial1.println(F("AT+CMGF=1"));
      delay(200);
      //if (res_at(debug(),"OK")){
      Serial1.println(F("AT+CMGS=\"+919885333843\""));
      Serial.println("-- debug  3");
      delay(200);
      // if(res_at(debug(),">")){
      Serial1.println("Emergency Help for Srilakshmi  ,pls reach her   ");
      Serial.println("-- debug  4");
      Serial1.println("www.google.com/maps?q=16.254382,80.3223094"); 
      delay(200);
      Serial1.println("");
      delay(200);
      Serial1.write(0x1A);
      delay(200);
      Serial.println("-- sms done ");
      Serial1.flush();
      
}
