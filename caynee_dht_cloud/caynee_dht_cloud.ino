// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include "DHT.h"

#define DHTPIN 5     // GPIO5 - D1 - Nodemcu 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// WiFi network info.
char ssid[] = "Quality Thought 605B";
char wifiPassword[] = "roundtable";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "6fff5240-f05c-11e6-a971-4db18559717d";
char password[] = "4a5495303e20c8e904dab1862802bb32990cd994";
char clientID[] = "c9f5f4c0-6571-11e9-933e-cf08617625ed";

//unsigned long lastMillis = 0;

void setup() {
  // DO WIFI CONNECTIVITY 

  // CLOUD CONNECTITY 

  
	Serial.begin(9600);
 pinMode(LED_BUILTIN, OUTPUT);
 dht.begin();
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  // Connect to WIFI 
  // Connect to Cayenne Server 
  // Transmit the data 
}

void loop() {
	Cayenne.loop();

    // READ DATA FROM SENSORS 
     // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // CONTROL A FAN 

  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    dht.begin();
    h = dht.readHumidity();
    t = dht.readTemperature();
    f = dht.readTemperature(true);
    
    return;
  }


  if(h>75){
    // write a control logic to turn on a fan or any device 
    digitalWrite(LED_BUILTIN,HIGH); // turn on device 
    delay(1000);
    digitalWrite(LED_BUILTIN,LOW);
    delay(1000);
    
    }else if(h<75){
            digitalWrite(LED_BUILTIN,LOW);
    
      }else{
        // do nothing 
        
        }
    
  
	//Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
	//if (millis() - lastMillis > 10000) {
	//	lastMillis = millis();
		//Write data to Cayenne here. This example just sends the current uptime in milliseconds.

   // UPLOAD SECTION 
   
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
