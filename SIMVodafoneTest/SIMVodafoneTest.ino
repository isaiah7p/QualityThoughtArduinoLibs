
#include <SoftwareSerial.h>




// SIM Module setup
SoftwareSerial sim800l(10, 11); //RX - TX



void setup() {

    sim800l.begin(115200);
    Serial.begin(115200);
      //sim800l.listen();
      Serial.println("sim800...........");

      sim800l.println(F("AT"));
      delay(200);

      
      
      //Serial.println(debug());
//      sim800l.println(F("AT+CBC"));
//      delay(200);
//      
//      //Serial.println(debug());
//
//      sim800l.println(F("AT+CSQ"));
//      delay(200);
//
//      sim800l.println(F("AT+CMGF=1"));
//      delay(200);
      //if (res_at(debug(),"OK")){
     // sim800l.println(F("AT+CMGS=\"+919676867575\""));//
     // delay(200);
      // if(res_at(debug(),">")){


      
      sim800l.println(F("AT+QLTS"));
      
      
//      sim800l.println("Emergency Help for Isaiah  DD ,pls reach him  ");
//      sim800l.print("maps.google.com/?q=");
     // sim800l.print(flat, 6);
     // sim800l.print(",");
     // sim800l.print(flon, 6);
    //  sim800l.println(" HEALTH CARD  : 7869 7868 6778 1234");
     // sim800l.println(pitchVal);
     // sim800l.println(rollVal);
     // sim800l.println("Speed:");
     // sim800l.println(gpsSpeed);



      //sim800l.println("maps.google.com");
      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);


      
      // env_sms();
      // i++;
    //  alertSMS = false;

     // hac_llam();

} // setup ends here







// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
      //// Emergency Contact to Isaiah : 

   

}

void hac_llam() {
  //sim800l.listen();
  sim800l.println(F("ATD+919676867575;"));
  delay(500);
  Serial.println("Calling IN_CASE_OF_EMERGENCY_NUMBERS");
}

/***********************************************************************************************************************************/

