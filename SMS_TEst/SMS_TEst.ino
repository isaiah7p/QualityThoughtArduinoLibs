#include <SoftwareSerial.h>
SoftwareSerial sim800l(10, 11); //RX - TX 

void setup() {
  // put your setup code here, to run once:
        Serial.begin(9600);
      sim800l.begin(115200);       
       Serial.println("Sending  SMS  "); 
      sim800l.listen();
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

      sim800l.println("Emergency Help for Test  ,pls reach her at below location  ");
      
    //  sim800l.print("maps.google.com/?q=17.5379461,78.3825534");  //17.5379461,78.3825534
      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);
      delay(200);

      //sim800l.begin(115200);       
       Serial.println("getting  GPS  "); 
      sim800l.listen();
      Serial.println("-- test -- Phone ");

      sim800l.println(F("AT"));
      delay(200);
      sim800l.println(F("AT+SAPBR=3,1, \"CONTYPE\",\"GPRS\""));
      sim800l.println(F("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\""));
      sim800l.println(F("AT+SAPBR=1,1")); 
      sim800l.println(F("AT+CIPGSMLOC=1,1"));
      delay(200);
      //Serial.print();
}

void loop() {
  // put your main code here, to run repeatedly:

}
