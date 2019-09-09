#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP UDP;


const char *ssid = "mrhyde17";
const char *password = "abc89";

const uint16_t UDP_LOCAL_PORT =  8050;
const uint16_t UDP_REMOTE_PORT = 8051;
const char UDP_REMOTE_HOST[] =   "receiver";
char TRIGGER_STRING[] = "somestring";


void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


Serial.println("PROGRAM: starting UDP");
if (UDP.begin(UDP_LOCAL_PORT) == 1)
{
  Serial.println("PROGRAM: UDP started");
}
else
{
  Serial.println("PROGRAM: UDP not started");
}

  
}

void loop() {
  // put your main code here, to run repeatedly:
pinMode(2, LOW);
delay(1000);
Serial.println("PROGRAM: sending trigger");
UDP.beginPacket(UDP_REMOTE_HOST, UDP_REMOTE_PORT);
UDP.write(TRIGGER_STRING);
UDP.endPacket();

pinMode(2, HIGH);
delay(1000);

}

