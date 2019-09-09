// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include "DHT.h"

#define DHTPIN 5     // GPIO5 - D1 - Nodemcu 
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
// WiFi network info.
char ssid[] = "Venom";
char wifiPassword[] = "b4b3c69b";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "adfbe290-52cd-11e9-86b5-4fe3d2557533";
char password[] = "5425a38a2f4bfb50780b9263bbbc364ed56bbfb7";
char clientID[] = "c2e7df60-52cd-11e9-ba40-5d168a516101";

//unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
 dht.begin();
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  // Connect to WIFI 
  // Connect to Cayenne Server 
  // Transmit the data 
}

void loop() {
  Cayenne.loop();
     // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);


  //Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
  //if (millis() - lastMillis > 10000) {
  //  lastMillis = millis();
    //Write data to Cayenne here. This example just sends the current uptime in milliseconds.
    Cayenne.virtualWrite(0, h);
    Cayenne.virtualWrite(1, t);
    Cayenne.virtualWrite(2, f);
    //Some examples of other functions you can use to send data.
    //Cayenne.celsiusWrite(1, 22.0);
    //Cayenne.luxWrite(2, 700);
    //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
  //}
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
