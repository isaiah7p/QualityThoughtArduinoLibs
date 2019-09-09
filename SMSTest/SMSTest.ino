#include "Wire.h"

int timesTosend=1;
int count=0;
char phone_no[]="9676867575";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //delay(2000);
  // Serial.print("AT_CMGF=1");
 // delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
       while(count<timesTosend){
         delay(1500);
         Serial.print("AT+CMGS=\\");
         Serial.print(phone_no);
         Serial.println("\\");
             while(Serial.read()!=0){
              Serial.println("Test SMS from Arduino GSM ... Hello Darling ");
              delay(500);
              Serial.write(0x1A);
              Serial.write(0x0D);
              Serial.write(0x0A);
    
              delay(5000);
              }
          count++;
    
        }
    
    }


