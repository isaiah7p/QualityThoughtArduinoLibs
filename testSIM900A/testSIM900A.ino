
#include <SoftwareSerial.h>

SoftwareSerial sim800l(10, 11); //RX - TX 
void setup() {

  Serial.begin(115200);Serial.println("insetup method ");
   sim800l.begin(9600);
   
  

}

void loop() {
  // put your main code here, to run repeatedly:
  //put your setup code here, to run once:


      Serial.println("loop method ");
      
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
     // sim800l.println(F("AT+CMGS=\"+919848477144\""));//
      sim800l.println(F("AT+CMGS=\"+919676867575\""));//
      delay(200);
      // if(res_at(debug(),">")){
      sim800l.println("Emergency Help  ,pls reach her at below location  ");
      sim800l.print("maps.google.com/?q=");
     // sim800l.print(flat, 6);
      //sim800l.print(",");
     // sim800l.print(flon, 6);
      sim800l.print("Niharika is Available Facebook Tracking Link");
    //  sim800l.print("www.facebook.com/niharika.roy.545");
      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);
      delay(200);
}
