
/* This Sketch will get the GSM Network time using AT commands 
 * 
 * the time is only set when the GSM card is initialized, so 
 * the time seems to never get updated.  I'll work on that.
 *
 * time response format: 
 * <cr><lf>+QLTS: "yy/MM/dd,hh:mm:sszzz,x"<cr><lf>
 * where:
 *  <cr> = binary decimal 13 (carrage return)
 *  <lf> = binary decimal 10 (line feed)
 *   yy  = year
 *   MM  = month (1=jan)
 *   dd  = day of month
 *   hh  = hour (24 hour)
 *   mm  = minute
 *   ss  = second
 *   zzz = +/- quarter hours to GMT
 *   x   = 1 is daylight savings, 0 is not 
 * 
 * example:
 * <cr><lf>+QLTS: "15/02/20,01:03:28-20,0"<cr><lf>
 *
 * Arduino 1.6.0 IDE
 * Arduino UNO R3
 * Arduino GSM Shield R3
 * Quectel M10ER01A06W32
 * T-Mobile Pay as you go SIM ($3/month on 2015)
 * Annapolis, MD, USA
 *
 */

#include <GSM.h>

#define MY_BUFFER_SIZE 30

GSM gsmAccess(false);  // pass in true to see debug information
int timeout = 5000; // 5 seconds

char myBuffer[MY_BUFFER_SIZE];
int start;
bool resp;

void setup()
{
  Serial.begin(9600);
    
  Serial.println("Connecting to the GSM network");
  
  boolean notConnected = true;
  while(notConnected) {
    Serial.println(gsmAccess.begin());
    if(gsmAccess.begin() == GSM_READY) // Note: I do not require PIN #
    
      notConnected = false;
    else {
      Serial.println("Not connected, trying again");
      delay(1000);
    }
  }
  Serial.println("Connected");
  
  Serial.println("sending AT+QLTS");
  theGSM3ShieldV1ModemCore.genericCommand_rqc("AT+QLTS");
  myBuffer[0] = 0;
  start = millis();
  while((millis() - start) < timeout) {
    theGSM3ShieldV1ModemCore.genericParse_rsp(resp, "QLTS", "OK");
    if(resp) {
      if(theGSM3ShieldV1ModemCore.theBuffer().extractSubstring("+QLTS: \"", "\"", myBuffer, 100)) {
        break;
      }
    }
  }
  if(myBuffer[0]) {
    Serial.print("GSM clock = ");
    Serial.println(myBuffer);
  } else
    Serial.println("GSM clock = nothing");
}

void loop()
{
 Serial.print("GSM clock = ");
    Serial.println(myBuffer);
}

