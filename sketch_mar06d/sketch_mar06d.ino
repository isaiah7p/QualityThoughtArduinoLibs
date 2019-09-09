#include <ESP8266WiFi.h>
byte sendEmail(int x);
byte eRcv(WiFiClientSecure client);


const char* SSID = "joelgloria"; 
const char* PASS = "b4b3c69b5267!"; 
const char* user_base64 = " your e-mail adress (convert in base64encode) "; // https://www.base64encode.org/
const char* user_password_base64 = "your e-mail password (convert in base64encode) "; 
const char* from_email = "MAIL From: < your e-mail >"; 
const char* to_email = "RCPT TO: < To which the email is sent >"; 
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  Serial.print("Connecting To ");
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if(sensorValue <100){
       if (sendEmail(sensorValue)) Serial.println(F("Email sent"));
       else Serial.println(F("Email failed"));
  }
  delay(1000);
}

byte sendEmail(int x) 
{
  WiFiClientSecure client;
  if (client.connect("smtp.gmail.com", 465) == 1) Serial.println(F("connected"));
  else {   Serial.println(F("connection failed"));   return 0; }
  
  if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending EHLO")); client.println("EHLO 1.2.3.4"); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending login")); client.println("AUTH LOGIN"); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending User base64")); client.println(user_base64); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending Password base64")); client.println(user_password_base64); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending From")); client.println(from_email); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending To")); client.println(to_email); if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending DATA")); client.println(F("DATA")); if (!eRcv(client)) return 0;
  client.println(F("Subject: E-mail poruka\r\n"));
  client.println(F("******Upali svetlo gazda:\n"));
  client.println(x);
  client.println(F("."));
  if (!eRcv(client)) return 0;
  Serial.println(F("--- Sending QUIT"));
  client.println(F("QUIT"));
  if (!eRcv(client)) return 0;
  client.stop();
  return 1;
}

byte eRcv(WiFiClientSecure client)
{
  byte respCode;
  byte thisByte;
  int loopCount = 0;

  while (!client.available()) {
    delay(1);
    loopCount++;
    if (loopCount > 10000) {
      client.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  respCode = client.peek();
  while (client.available())
  {
    thisByte = client.read();
    Serial.write(thisByte);
  }
  if (respCode >= '4')return 0;
  return 1;
}
