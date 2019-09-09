#include <SoftwareSerial.h>
SoftwareSerial softSerial(8, 9); // RX, TX
int i = 0;
void setup() 
{
  uint32_t baud = 9600;
  Serial.begin(baud);
  softSerial.begin(baud);
  Serial.print("SETUP!! @");
  Serial.println(baud);
}

void loop() 
{   
    if(i==0)
      {
      
        Serial.println("IN Loop");
   
    while(softSerial.available() > 0) 
    {
      char a = softSerial.read();
        Serial.println(a);
      if(a == '\0')
        continue;
      if(a != '\r' && a != '\n' && (a < 32))
        continue;
      Serial.print(a);
    }
    
    while(Serial.available() > 0)
    {
      char a = Serial.read();
       Serial.println(a);
      Serial.write(a);
      softSerial.write(a);
    }
    
    i++;
  } // if condition
}
