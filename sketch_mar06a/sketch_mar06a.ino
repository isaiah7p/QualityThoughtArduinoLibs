#include <SoftwareSerial.h>;

void setup() {
  // put your setup code here, to run once:
      SoftwareSerial sim800l(10, 11); //RX - TX
      Serial.begin(9600);
      sim800l.begin(9600);

      //sim800l.listen();
      Serial.println("-- SUBBU -- Phone ");

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
      sim800l.println(F("AT+CMGS=\"+919676867575\""));//
      delay(200);
      // if(res_at(debug(),">")){
      sim800l.println("Emergency Help for Subash DD ,pls reach him  ");
      sim800l.print("maps.google.com/?q=");
     // sim800l.print(flat, 6);
     // sim800l.print(",");
     // sim800l.print(flon, 6);
    //  sim800l.println(" HEALTH CARD  : 7869 7868 6778 1234");
     // sim800l.println(pitchVal);
     // sim800l.println(rollVal);
     // sim800l.println("Speed:");
     // sim800l.println(gpsSpeed);
   sim800l.println(F("AT+CGATT =1"));
    sim800l.println(F("AT+SAPBR =3,1,”CONTYPE”,”GPRS”"));
     sim800l.println(F("AT+SAPBR =3,1,”APN”,”RCMNET”"));
      sim800l.println(F("AT+SAPBR=1,1"));
       sim800l.println(F("AT+SAPBR=2,1"));
        sim800l.println(F("AT+CIPGSMLOC=1,1")); 
        sim800l.println(F("AT"));
  AT+CGATT =1 // to attach GPRS.

  AT+SAPBR =3,1,”CONTYPE”,”GPRS” //activate bearer profile.

  AT+SAPBR =3,1,”APN”,”RCMNET”

  AT+SAPBR=1,1

  AT+SAPBR=2,1

  AT+CIPGSMLOC=1,1 //to get gsm location, time and date.

  AT+CIPGSMLOC=2,1 //to get gsm time and date

  AT+SAPBR =0,1 //to deactivate bearer profile.

      //sim800l.println("maps.google.com");
      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);
      delay(200);

}

void loop() {
  // put your main code here, to run repeatedly:

}
