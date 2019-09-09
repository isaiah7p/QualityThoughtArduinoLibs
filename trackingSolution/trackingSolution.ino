# Seconds Hold Program “


#include "TinyGPS.h"
#include <SoftwareSerial.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


TinyGPS gps;
//
int unoRxPin = 10; // connected to TX pin of the GPS
int unoTxPin = 11; // connected to RX pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);
long startMillis;
long secondsToFirstLocation = 0;
float gpsSpeed ;
float flat = 0;
float flon = 0;


String gpsString="";
char *test="$GPGGA";
String latitude="No Range ";
String longitude="No Range ";
int temp=0,i;
boolean gps_status=0;


// SIM Module setup
//SoftwareSerial sim800l(10, 11); //RX - TX 

 // buzzer 
int piezoPin = 8;



int inPin = 7;  // the pin number for input (for me a push button)
int ledPin = 13; 

int current;         // Current state of the button
                     // (LOW is pressed b/c i'm using the pullup resistors)
long millis_held;    // How long the button was held (milliseconds)
long secs_held;      // How long the button was held (seconds)
long prev_secs_held; // How long the button was held in the previous check
byte previous = HIGH;
unsigned long firstTime; // how long since the button was first pressed 


void setup() {

lcd.begin(16,2);

 
  pinMode(ledPin, OUTPUT);
  digitalWrite(inPin, HIGH);  // Turn on 20k pullup resistors to simplify switch input
 // put your setup code here, to run once:
 
ss.begin(115200);
Serial.begin(115200);
//sim800l.begin(115200);

Serial.println("SetUP ");

ss.begin(9600); lcd.print("GPS Tracking"); lcd.setCursor(0,1); lcd.print(" System "); delay(2000); //gsm_init(); lcd.clear(); //Serial.println("AT+CNMI=2,2,0,0,0"); lcd.print("GPS Initializing"); lcd.setCursor(0,1); lcd.print(" No GPS Range ");
get_gps(); delay(2000);
lcd.clear(); lcd.print("GPS Range Found"); lcd.setCursor(0,1); lcd.print("GPS is Ready"); delay(2000);
lcd.clear(); lcd.print("System Ready"); temp=0;


}

void loop() {

// incase of long press of button starts here 

  current = digitalRead(inPin);

  // if the button state changes to pressed, remember the start time 
  if (current == LOW && previous == HIGH && (millis() - firstTime) > 200) {
    firstTime = millis();
  }

  millis_held = (millis() - firstTime);
  secs_held = millis_held / 1000;

  // This if statement is a basic debouncing tool, the button must be pushed for at least
  // 100 milliseconds in a row for it to be considered as a push.
  if (millis_held > 50) {

    if (current == LOW && secs_held > prev_secs_held) {
      ledblink(1, 50, ledPin); // Each second the button is held blink the indicator led
    }

    // check if the button was released since we last checked
    if (current == HIGH && previous == LOW) {
      // HERE YOU WOULD ADD VARIOUS ACTIONS AND TIMES FOR YOUR OWN CODE
      // ===============================================================================

      // Button pressed for less than 1 second, one long LED blink
      if (secs_held <= 0) {
        ledblink(1,750,ledPin);
      }

      // If the button was held for 3-6 seconds blink LED 10 times
      if (secs_held >= 1 && secs_held < 3) {
        ledblink(10,200,ledPin); 
      }

      // Button held for 1-3 seconds, print out some info
      if (secs_held >= 3) {

      // piezo buzzer 

    tone( piezoPin, 2000, 500);
 
    delay(1000);


     //  call GPS and  send SMS information get data 
      // put your main code here, to run repeatedly:
    Serial.println("loop "); 
    if(ss.available()){
           Serial.println(" GPS Available  ");    
      }else{
        Serial.println("  GPS Not Available  "); 
        }
    bool newData = false;
    unsigned long chars = 0;
    unsigned short sentences, failed;

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
     // Serial.print("  !!!  GPS SPeed =");
     // Serial.print(gpsSpeed);

      if (chars == 0) {
        // if you haven't got any chars then likely a wiring issue
       // lcd2.setCursor(0, 2);          // set cursor to column 0, row 0 (the first row)
        Serial.print("No GPS: check wiring");
      }
      else if (secondsToFirstLocation == 0) {
        // if you have received some chars but not yet got a fix then indicate still searching and elapsed time
        //lcd2.clear();  // start with a blank screen

        long seconds = (millis() - startMillis) / 1000;

        //lcd2.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
       // lcd2.print("Searching ");
        for (int i = 0; i < seconds % 4; ++i) {
         // lcd2.print(".");
        }

        //lcd2.setCursor(0, 1);
        //lcd2.print("Elapsed time:");
        //lcd2.print(seconds);
        //lcd2.print("s");
      }

    }

     Serial.println("-- SMS -- Phone ");

     sim800l.println(F("AT"));
     delay(200);
     //Serial.println(debug());
      sim800l.println(F("AT+CBC"));
      delay(200);
      //Serial.println(debug());

    sim800l.println(F("AT+CSQ"));
     delay(200);
//
      sim800l.println(F("AT+CMGF=1"));
     delay(200);
     //if (res_at(debug(),"OK")){
   //  sim800l.println(F("AT+CMGS=\"+919005532069\""));//
     sim800l.println(F("AT+CMGS=\"+919676867575\""));//
      delay(200);
      // if(res_at(debug(),">")){
      sim800l.println("Emergency Help for Test   ,pls reach him  ");
      sim800l.print("maps.google.com/?q=");
      sim800l.print(flat, 6);
     sim800l.print(",");
      sim800l.print(flon, 6);
//    //  sim800l.println(" HEALTH CARD  : 7869 7868 6778 1234");
//
//
//      //sim800l.println("maps.google.com");
      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);
      delay(200);

  delay(1000);

  
         
    

  // SMS part  ends here … 

      }
      // ===============================================================================
    }
  }

  previous = current;
  prev_secs_held = secs_held;
}

// Just a simple helper function to blink an led in various patterns
void ledblink(int times, int lengthms, int pinnum){
  for (int x=0; x<times;x++) {
    digitalWrite(pinnum, HIGH);
    delay (lengthms);
    digitalWrite(pinnum, LOW);
    delay(lengthms);
  }
}


void serialEvent() {   while(Serial.available())   

{     if(Serial.find("Track Vehicle"))     {     
  temp=1;      
break;   
  }    
else     
temp=0;  
}
 }
void gpsEvent() {  
gpsString="";   
while(1)   {    
while (gps.available()>0)            //checking serial data from GPS    {     
char inChar = (char)gps.read();      
gpsString+= inChar;                    //store data from GPS into gpsString      i++;      if (i < 7)                            {       if(gpsString[i-1] != test[i-1])         //checking for $GPGGA sentence       {         i=0;         gpsString="";       }      }     if(inChar=='\r')     {      if(i>65)      {        gps_status=1;        break;      }      else      {        i=0;      }     }   }    if(gps_status)     break;   } }
void gsm_init() {   
lcd.clear();   
lcd.print("Finding Module..");   
boolean at_flag=1;   
while(at_flag)   {     
Serial.println("AT");    
while(Serial.available()>0)     {      
if(Serial.find("OK"))      
at_flag=0;     }         
delay(1000);   }
  lcd.clear();   
  lcd.print("Module Connected..");   
delay(1000);   
lcd.clear();   
lcd.print("Disabling ECHO");   
boolean echo_flag=1;   
while(echo_flag)   {     
Serial.println("ATE0");     
while(Serial.available()>0)     {       
if(Serial.find("OK"))      
echo_flag=0;    
}     
delay(1000);   }
  lcd.clear();   lcd.print("Echo OFF");   delay(1000);   lcd.clear();   lcd.print("Finding Network..");   boolean net_flag=1;   while(net_flag)   {     Serial.println("AT+CPIN?");     while(Serial.available()>0)     {       if(Serial.find("+CPIN: READY"))       net_flag=0;     }     delay(1000);   }   lcd.clear();   lcd.print("Network Found..");   delay(1000);   lcd.clear(); }
void get_gps() {    gps_status=0;    int x=0;    while(gps_status==0)    {     gpsEvent();     int str_lenth=i;     latitude="";     longitude="";     int comma=0;     while(x<str_lenth)     {       if(gpsString[x]==',')       comma++;       if(comma==2)        //extract latitude from string       latitude+=gpsString[x+1];            else if(comma==4)        //extract longitude from string       longitude+=gpsString[x+1];       x++;     }     int l1=latitude.length();     latitude[l1-1]=' ';     l1=longitude.length();     longitude[l1-1]=' ';     lcd.clear();     lcd.print("Lat:");     lcd.print(latitude);     lcd.setCursor(0,1);     lcd.print("Long:");     lcd.print(longitude);     i=0;x=0;     str_lenth=0;     delay(2000);    } }
void init_sms() {   Serial.println("AT+CMGF=1");   delay(400);   Serial.println("AT+CMGS=\"+919676867575\"");   // use your 10 digit cell no. here   delay(400); }
void send_data(String message) {   Serial.println(message);   delay(200); }
void send_sms() {   Serial.write(26); }
void lcd_status() {   lcd.clear();   lcd.print("Message Sent");   delay(2000);   lcd.clear();   lcd.print("System Ready");   return; }
void tracking() {     init_sms();     send_data("Vehicle Tracking Alert:");     send_data("Your Vehicle Current Location is:");     Serial.print("Latitude:");     send_data(latitude);     Serial.print("Longitude:");     send_data(longitude);     send_data("Please take some action soon..\nThankyou");     send_sms();     delay(2000);     lcd_status(); }



