#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); //RX - TX 
boolean isGPRSInit = false;
String Location ="";
String mobileNumber="+919676867575";
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  while (!Serial) {
  }
  // initialize the pushbutton pin as an input:
 // pinMode(sensorPin, INPUT);
  // Attach an interrupt to the ISR vector
 // attachInterrupt(0, pin_ISR, FALLING);
}

/////////***GSM RESPONSE***///////////
String DisplayGSMResponse() {
  if(mySerial.available()) {
    String gsm_input="";
    while(mySerial.available()) {
      gsm_input+= (char)mySerial.read();
    }
    gsm_input.trim();
    delay(1000);
    Serial.println(gsm_input);
    return gsm_input;
  }
}

void SendMessage(String mobNum,String Location) {
  Serial.println("Sending message..");
  mySerial.println("AT+CMGF=1");
  //Sets the GSM Module in Text Mode
  delay(2000);
  // Delay of 1000 milli seconds or 1 second
  DisplayGSMResponse();
  mySerial.println("AT+CMGS=\""+mobNum+"\"\r");
  // mobile Number
  delay(4000);
  DisplayGSMResponse();
 // cleanBuffer();
  mySerial.print("test");
  // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);
  // ASCII code of CTRL+Z
  delay(8000);
  DisplayGSMResponse();
}

void gprsInit() {
  if (isGPRSInit) {
    return;
  }
  Serial.println("GPRS INITIALIZING");
  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  DisplayGSMResponse();
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"INTERNET\"");
  delay(2000);
  DisplayGSMResponse();
  mySerial.println("AT+SAPBR=1,1");
  delay(8000);
  DisplayGSMResponse();
  mySerial.println("AT+SAPBR=2,1");
  delay(2000);
  DisplayGSMResponse();
  isGPRSInit = true;
}

void gprsterm() {
  mySerial.println("AT+SAPBR=0,1");
  delay(1000);
  DisplayGSMResponse();
  isGPRSInit = false;
}

String getGPS() {
  Serial.println("GETTING GPS LOCATION");
  String loc = "";
  String location = "";
  mySerial.println("AT+CIPGSMLOC=1,1");
  delay(3000);
  loc = DisplayGSMResponse();
  return location;
}

void loop() {
      mySerial.listen();
      //Serial.println("-- test -- Phone ");

      mySerial.println(F("AT"));
      delay(200);
  
    mySerial.println(F("AT+CIPGSMLOC=1,1"));
    delay(200);
//  
//  
// // if (buttonState == 1) {
//    detachInterrupt(0);
//    gprsInit();
//    Serial.println( getGPS());
//    SendMessage(mobileNumber, getGPS());
//    gprsterm();
//    Serial.println("location = " + getGPS());
//   // buttonState = 0;
//    location = "";
   // attachInterrupt(0, pin_ISR, FALLING );
 // }
}

void pin_ISR() {
 // buttonState = 1;
  Serial.println("interrupt");
}
