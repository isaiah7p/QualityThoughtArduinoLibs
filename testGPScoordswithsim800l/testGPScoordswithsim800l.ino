#include <SoftwareSerial.h>
SoftwareSerial SIM800(10, 11); // RX, TX
String a;
String b;


void setup()
{
  Serial.begin(9600);  //harware serial
  SIM800.begin(9600);  //bluetooth module, for sending AT-commands
  SIM800.print("ATZ\r\n");
  SIM800.print("ATE0\r\n");
}




void loop()
{
  if (SIM800.available())
  {
  a = SIM800.readString();  //data from bluetooth
  SIM800.print("AT+CSQ\r\n");
  if (a.indexOf("+CSQ") > 0)
  {
  b = SIM800.readString();
  }


  if (a == "\r\nRING\r\n")
  {
  SIM800.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  SIM800.print("AT+CMGS=\"*\"\r\n");
  delay(200);
  SIM800.print(b); //kunhan jotain dataa
  SIM800.print("\r\n");
  delay(500);
  SIM800.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  SIM800.print("\r\n");
  }
  }
}
 
