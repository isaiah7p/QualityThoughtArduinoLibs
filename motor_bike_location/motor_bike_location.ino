
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include <TinyGPS++.h>
 
SMSGSM sms;

static const int RXPin = 7, TXPin = 8;
static const uint32_t GPSBaud = 9600; 

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

char message[160];

char datetime[24];
char latitude[12];
char longitude[12];

char number[]="123123123";

char text[160];
char pos;
char *p;
char *c;

 
void setup()
{
 Serial.begin(9600);
 ss.begin(GPSBaud);
 Serial.println("START");
 gsm.begin(2400);
 sms.SendSMS("123123123", "system ok"); // on setup SMS is sent to my number letting me know device is ON
}
 
void loop()
{
     while (ss.available() > 0)
    if (gps.encode(ss.read()))
        if (gps.location.isValid())
  {
        
        strcat(text, "comgooglemaps://?q=");
        dtostrf(gps.location.lat(), 1, 6, latitude);
        strcat(text,latitude);
        strcat(text,",");
        dtostrf(gps.location.lng(), 1, 6, longitude);
        strcat(text,longitude);

  }  
  
 pos=sms.IsSMSPresent(SMS_UNREAD);
 Serial.println((int)pos);
 
 if((int)pos>0&&(int)pos<=20){
   Serial.print("Incomming message, POS=");
   Serial.println((int)pos);
   message[0]='\0';
   sms.GetSMS((int)pos,number,message,180);
   p=strstr(message,"Rotor");
   
   if(p)
   {     
     Serial.println("Success");
     Serial.println(text);
     sms.SendSMS(number, text);  // When anybody send SMS with password=="Rotor"  ==> device sends back coordinates in mobile link to google maps
   }
 }
 
   sms.DeleteSMS((int)pos);  
 
 
 
 delay(5000);
 
}

