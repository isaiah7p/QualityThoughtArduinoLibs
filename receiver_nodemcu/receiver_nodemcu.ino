#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP UDP;


const char *ssid = "mrhyde17";
const char *password = "abc89";


const uint16_t UDP_LOCAL_PORT =  8051; // Must match UDP_REMOTE_PORT on sender
char TRIGGER_STRING[] = "somestring";  // Must match TRIGGER_STRING on sender

void setup() {
  // put your setup code here, to run once:

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
  char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; // buffer to hold incoming packet,
int packetSize = UDP.parsePacket();
if (packetSize > 0)
{
  Serial.print("PROGRAM: received UDP packet of size ");
  Serial.println(packetSize);
  Serial.print("PROGRAM: from ");
  IPAddress remote = UDP.remoteIP();
  for (int i = 0; i < 4; i++)
  {
    Serial.print(remote[i], DEC);
    if (i < 3)
    {
      Serial.print(".");
    }
  }
  Serial.print(", port ");
  Serial.println(UDP.remotePort());
  UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
  Serial.print("PROGRAM: contents: ");
  Serial.println(packetBuffer);
  if (strncmp(packetBuffer, TRIGGER_STRING, strlen(TRIGGER_STRING)) == 0)
  {
    Serial.println("PROGRAM: trigger received");
    // DO YOUR STUFF HERE
  }
  delay(10);
}

}

