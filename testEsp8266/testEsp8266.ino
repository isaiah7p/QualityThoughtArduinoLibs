#include "UbidotsMicroESP8266.h"
#define TOKEN  "madmax"  // Put here your Ubidots TOKEN
#define WIFISSID "DustDevils"
#define PASSWORD "b4b3c69b"

Ubidots client(TOKEN);

void setup(){
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){
    float value = analogRead(A0);
    client.add("Temperature", value);
    client.sendAll(true);
}
