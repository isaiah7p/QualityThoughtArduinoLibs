#include <SoftwareSerial.h>
// SIM Module setup
SoftwareSerial sim800l(10, 11); //RX - TX


void setup() {
  
  // put your setup code here, to run once:
      sim800l.begin(9600);
    sim800l.println("-- SUBBU -- Phone ");
      sim800l.listen();
  

      //// Emergency Contact to Isaiah : 

      //sim800l.listen();
      sim800l.println("sim800...........");

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
      sim800l.print(",");
     // sim800l.print(flon, 6);
     sim800l.println(" HEALTH CARD  : 7869 7868 6778 1234");
      sim800l.println("");
      sim800l.println("");
      sim800l.println("Speed:");
      sim800l.println("");



      //sim800l.println("maps.google.com");
      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);


}

void loop() {
  // put your main code here, to run repeatedly:

   

      

}
