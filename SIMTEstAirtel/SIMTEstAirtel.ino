#include <SoftwareSerial.h>

SoftwareSerial sim800l(10, 11); //RX - 
int backLight = 13; 

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  sim800l.begin(115200);
  sim800l.listen();
  Serial.println(F("SETUP"));
pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.

Serial.println(" Test SMS ");

 sim800l.println(F("AT"));
     delay(200);
    //Serial.println(debug());
      sim800l.println(F("AT+CBC"));
      delay(200);
      //Serial.println(debug());

      sim800l.println(F("AT+CSQ"));
      delay(200);

      sim800l.println(F("AT+CMGF=1"));
      delay(200);
      //if (res_at(debug(),"OK")){
      sim800l.println(F("AT+CMGS=\"+919676867575\""));
      
     // sim800l.println(F("AT+CMGS=\"51555\""));// FaceBook Update 
      delay(200);
      // if(res_at(debug(),">")){
      sim800l.println("5267  Im in Emergency,pls reach me at below Location  ");
   //   sim800l.print("maps.google.com/?q=");

      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);
     delay(200);
  
  Serial.println(F("Done Set UP "));
}

void loop() {

  Serial.println(" Test SMS ");

     sim800l.println(F("AT"));
     delay(200);
    //Serial.println(debug());
      sim800l.println(F("AT+CBC"));
      delay(200);
      //Serial.println(debug());

      sim800l.println(F("AT+CSQ"));
      delay(200);

      sim800l.println(F("AT+CMGF=1"));
      delay(200);
      //if (res_at(debug(),"OK")){
      sim800l.println(F("AT+CMGS=\"+919676867575\""));
      
     // sim800l.println(F("AT+CMGS=\"51555\""));// FaceBook Update 
      delay(200);
      // if(res_at(debug(),">")){
      sim800l.println("5267  Im in Emergency,pls reach me at below Location  ");
   //   sim800l.print("maps.google.com/?q=");

      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);
     delay(200);

     
  
  // put your main code here, to run repeatedly:

}
