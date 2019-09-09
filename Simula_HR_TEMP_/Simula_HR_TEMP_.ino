// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling.
#include <Wire.h>
//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "WARLOCK";
char wifiPassword[] = "P@ssw0rdiot";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "851f51a0-965c-11e8-87b0-97a7dd91c15a";
char password[] = "6518112f44e68588f131127c8d23b41fec43d667";
char clientID[] = "4c174430-b41b-11e8-a5e0-433900986fca";

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(D1, D2);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();

    for(int i=0;i<20;i++){
     Cayenne.virtualWrite(0, i+67); // Heart Rate 
     Cayenne.virtualWrite(1, i+246);  // ECG 
     Cayenne.virtualWrite(2, i+82); // temp 
     delay(1000);
    } 

  //Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
//  if (millis() - lastMillis > 10000) {
//    lastMillis = millis();
//    //Write data to Cayenne here. This example just sends the current uptime in milliseconds.
//  
//    //Some examples of other functions you can use to send data.
//    //Cayenne.celsiusWrite(1, 22.0);
//    //Cayenne.luxWrite(2, 700);
//    //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
//  }
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
