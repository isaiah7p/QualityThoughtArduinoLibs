#include <SoftwareSerial.h>
#include "TinyGPS.h"

#define JOURNEY "b4b3c69b5267"

SoftwareSerial sim800l(10, 11); //RX - TX 
int inPin = 5;  // the pin number for input (for me a push button)
int ledPin = 3; // LED +VE 
const int sensorPin=A0;  // piezo buzzer 
int buzzerPin = 4;  // Buzzer PIN 
boolean liveOn = false;
int threshold= 1000;
int val = 0;
int buttonState = 0;
boolean alarm =false;

boolean transButton = false;

TinyGPS gps;
//
int unoRxPin = 6; // connected to TX pin of the GPS
int unoTxPin = 7; // connected to RX pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);


//int backLight = 13;    // pin 13 will control the backlight
//
long startMillis;
long secondsToFirstLocation = 0;
float gpsSpeed ;
float flat = 17.45257;
float flon = 78.421479;

    bool newData = false;
    unsigned long chars = 0;
    unsigned short sentences, failed;


String pvtKey="wY9DPG5vzpH99KNrNkx2";     // private key for posting data to sparkfun
String publicKey="w5nXxM6rp0tww5YVYg3G";  // public key for open page of sparkfun 
String url="";
String ip="\"api.thingspeak.com\"";        // sparkfun server ip or url
int port=80;                              // sparkfun server port

String SendCmd="AT+CIPSEND=";           // sending number of byte command
String Start="AT+CIPSTART=\"TCP\"";     // TCPIP start command 


// strings and variables
String msg="";
String instr="";
String str_sms="";
String str1="";

void setup() {

  
  // put your setup code here, to run once:
  Serial.begin(9600);
   sim800l.begin(115200);
    ss.begin(9600);
 
  
  startMillis = millis();
    pinMode(ledPin, OUTPUT);
    pinMode(inPin, INPUT);
    digitalWrite(buzzerPin, LOW);

   // digitalWrite(inPin, HIGH);  // Turn on 20k pullup resistors to simplify switch input
     buttonState = 0;
    Serial.println("-- setup -- Phone ");
    transButton = true;
//Serial.print("Initializing GSM");
//  initGSM();      // init GSM module
//
//  Serial.print("Initializing GPRS");
//  initGPRS();     // init GPRS in GSM Module
//
//  Serial.print("System Ready");
//  delay(2000);
}

void loop() {

sim800l.listen();



      
     // Get GPS Data 
        // put your main code here, to run repeatedly:
  // GPS Data Aquaring

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
       Serial.println(" have  new gps  data  ");
      // we have a location fix so output the lat / long and time to acquire
      if (secondsToFirstLocation == 0) {
        secondsToFirstLocation = (millis() - startMillis) / 1000;
      }

      // lcd2.clear();  // start with a blank screen

      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);
      gpsSpeed = gps.f_speed_kmph();

//      if (gpsSpeed >= topGPSSpeed) {
//
//        topGPSSpeed = gpsSpeed;
//
//
//      } else if (gpsSpeed >= topGPSSpeed) {
//        // do nothing
//      } else {
//        // do nothing
//      }


      // GPS Top Speed 
  //    Serial.print("Top Speed =");
  //    Serial.println(topGPSSpeed , 2);

      // lcd2.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
      Serial.print("Lat=");
      Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);

      //

      Serial.print("Long=");
      Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      Serial.print("  !!!  GPS SPeed =");
      Serial.print(gpsSpeed);

      if (chars == 0) {
        // if you haven't got any chars then likely a wiring issue
       // lcd2.setCursor(0, 2);          // set cursor to column 0, row 0 (the first row)
        Serial.print("No GPS: check wiring");
      }
      else if (secondsToFirstLocation == 0) {
        // if you have received some chars but not yet got a fix then indicate still searching and elapsed time
        //lcd2.clear();  // start with a blank screen

        long seconds = (millis() - startMillis) / 1000;

;
        for (int i = 0; i < seconds % 4; ++i) {
          Serial.print(".");
         // lcd2.print(".");
        }


      }

    }
    
        Serial.println(flat);
        Serial.println(flon);

        if(val >= threshold){
             val=0;
          }
          else{
            val = analogRead(sensorPin);
         }
          Serial.println(val);
      // val = analogRead(sensorPin);
        
  // put your main code here, to run repeatedly:

   //   Serial.println("-- SUBBU -- Phone ");
    
    Serial.println("-- loop -- Phone "); 
     Serial.println( digitalRead(inPin));

        delay(500);
  // if the button state changes to pressed, remember the start time 
      if(transButton){
        delay(5000);
      if(buttonState == 0){
        buttonState = digitalRead(inPin);
        }
        else{
           buttonState = 0;
        }
        transButton = false;
      }else{
         if(buttonState == 0){
        buttonState = digitalRead(inPin);
        }
        else{
           buttonState = 0;
        }
        }
      
      if (buttonState == 1 ||  val >= threshold ) {

        alarm = true;
        liveOn = true;
        Serial.println("In Trigger Condition Achived  "); 
        Serial.println(val); 
        Serial.println(buttonState);
        
        tone( buzzerPin, 100, 1000);  // alert everyone around ...
        
       for(int count=0;count<5;count++){
        digitalWrite(ledPin, HIGH);
        delay(100);
        digitalWrite(ledPin, LOW);
       }
 
 
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


      // gsm - gprs 
//
//      url="GET /input/";
//      url+=publicKey;
//      url+="?private_key=";
//      url+=pvtKey;
//      url+="&log=";
//      url+=msg;
//      url+=" HTTP/1.0\r\n\r\n";
//      String svr=Start+","+ip+","+port;
//      delay(1000);
//      connectGSM(svr,"CONNECT");
//      delay(1000);
//      int len = url.length();
//      String str="";
//      str=SendCmd+len;
//      sendToServer(str);
//       sim800l.print(url);
//      delay(1000);
//      sim800l.write(0x1A);
//      delay(1000);

     // Update FACEBOOK through Security Code & URL

      // maps.google.com/?q=18.0276135,79.5088303
/*
          Serial.println("Sending  FB Update   ");
             sim800l.listen();  
             sim800l.println(F("AT"));
            delay(200);
         
            sim800l.println(F("AT+CBC"));
           delay(200);

            sim800l.println(F("AT+CSQ"));
            delay(200);
      
            sim800l.println(F("AT+CMGF=1"));
            delay(200);
            //if (res_at(debug(),"OK")){
            sim800l.println(F("AT+CMGS=\"51555\""));//
            delay(200);
            // if(res_at(debug(),">")){
            sim800l.println("7096  Im in Emergency,pls reach me at below Location  ");
            sim800l.print("maps.google.com/?q=17.5379461,78.3825534");

            delay(200);
            sim800l.println();
            delay(200);
            sim800l.write(0x1A);
            delay(200);
       */

          

         // calling an emergency number 
            delay(1000);  

            hac_llam();

      }

  

      //delay(1500);
      buttonState = 0;
    //  val=0;
      delay(1000);
      
}

void hac_llam() {
 sim800l.listen();
 if(alarm){
 // sim800l.println(F("ATD+919676867575;"));
  sim800l.println(F("ATD+919848477144;"));
  delay(500);
  Serial.println("Calling IN_CASE_OF_EMERGENCY_NUMBERS");
 }
 alarm=false; 
}
void sendToServer(String str)
{
  sim800l.println(str);
  delay(1000);
}

void initGSM()
{
  connectGSM("AT","OK");
  connectGSM("ATE1","OK");
  connectGSM("AT+CPIN?","READY");
}
void initGPRS()
{
  connectGSM("AT+CIPSHUT","OK");
  connectGSM("AT+CGATT=1","OK");
  connectGSM("AT+CSTT=\"airtelgprs.com\",\"\",\"\"","OK");
  connectGSM("AT+CIICR","OK");
  delay(1000);
  sim800l.println("AT+CIFSR");
  delay(1000);
}
void connectGSM (String cmd, char *res)
{
  while(1)
  {
    Serial.println(cmd);
    sim800l.println(cmd);
    delay(500);
    while(sim800l.available()>0)
    {
      if(sim800l.find(res))
      {
        delay(1000);
        return;
      }
    }
    delay(1000);
   }
 }



