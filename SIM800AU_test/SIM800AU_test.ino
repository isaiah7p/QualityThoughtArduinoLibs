#include <SoftwareSerial.h>
 
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 10
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 11
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);
 
void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
//  //Being serial communication witj Arduino and SIM800
//  serialSIM800.begin(9600);
//  delay(1000);
//   
//  Serial.println("Setup Complete!");
//  Serial.println("Sending SMS...");
//   
//  //Set SMS format to ASCII
//  serialSIM800.write("AT+CMGF=1\r\n");
//  delay(1000);
// 
//  //Send new SMS command and message number
//  serialSIM800.write("AT+CMGS=\"+919676867575\"\r\n");
//  delay(1000);
//   
//  //Send SMS content
//  serialSIM800.write("TEST");
//  delay(1000);
//   
//  //Send Ctrl+Z / ESC to denote SMS message is complete
//  Serial.print(26, HEX);
//  serialSIM800.write((uint8_t) 26);
//  delay(1000);
//     
//  Serial.println("SMS Sent!");

  Serial.println("Test Started ");
    Serial.write("AT+CMGS=\""); // send the SMS number
    Serial.write("+919676867575");
    Serial.write("\"");
    delay(1000);

    delay(500);

    Serial.write(0x1A);
    Serial.write(0x0D);
    Serial.write(0x0A);
   Serial.println("SMS Sent!");
}
 
void loop() {
}

