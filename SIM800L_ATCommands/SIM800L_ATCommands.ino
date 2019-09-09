// SIM800L 

#include <SoftwareSerial.h>
SoftwareSerial sim800l(10, 11); //RX of SIM module - TX of SIM Module


void setup() {
  // put your setup code here, to run once:
   sim800l.begin(115200);
   
}

void loop() {
  // put your main code here, to run repeatedly:
       
       sim800l.listen();
       
       Serial.println("Sending  SMS  "); 
      
      Serial.println("-- test -- Phone ");

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
      //sim800l.println(F("AT+CMGS=\"+919848477144\""));//
      sim800l.println(F("AT+CMGS=\"+919676867575\""));//
      delay(200);
      // if(res_at(debug(),">")){
      sim800l.println("Emergency Help for Niharika  ,pls reach her at below location  ");
      sim800l.print("maps.google.com/?q=");
      sim800l.print(flat, 6);
      sim800l.print(",");
      sim800l.print(flon, 6);
      sim800l.print("Niharika is Available Facebook Tracking Link");
      sim800l.print("www.facebook.com/niharika.roy.545");
      
      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);
      delay(200);

// call option 

//sim800l.listen();
//
//  sim800l.println(F("ATD+919848477144;"));
//
//// GPRS Connection 
//
//void initGSM()
//{
//  connectGSM("AT","OK");
//  connectGSM("ATE1","OK");
//  connectGSM("AT+CPIN?","READY");
//}
//void initGPRS()
//{
//  connectGSM("AT+CIPSHUT","OK");
//  connectGSM("AT+CGATT=1","OK");
//  connectGSM("AT+CSTT=\"airtelgprs.com\",\"\",\"\"","OK");
//  connectGSM("AT+CIICR","OK");
//  delay(1000);
//  sim800l.println("AT+CIFSR");
//  delay(1000);
//}
//void connectGSM (String cmd, char *res)
//{
//  while(1)
//  {
//    Serial.println(cmd);
//    sim800l.println(cmd);
//    delay(500);
//    while(sim800l.available()>0)
//    {
//      if(sim800l.find(res))
//      {
//        delay(1000);
//        return;
//      }
//    }
//    delay(1000);
//   }
// }



}
