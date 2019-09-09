// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <DHT.h>
// WiFi network info.
char ssid[] = "Quality Thought 605B";
char wifiPassword[] = "roundtable";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "6fff5240-f05c-11e6-a971-4db18559717d";
char password[] = "4a5495303e20c8e904dab1862802bb32990cd994";
char clientID[] = "97d84fb0-3fbf-11e9-ad96-c15442ccb423";
  
unsigned long lastMillis = 0;
#define DHTPIN 5          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
	Cayenne.loop();

	//Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
	if (millis() - lastMillis > 500) {
	//	lastMillis = millis();
     float h = dht.readHumidity();
      float t = dht.readTemperature(); 
		if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
		//Write data to Cayenne here. This example just sends the current uptime in milliseconds.
		Cayenne.virtualWrite(0, h);
		  Cayenne.virtualWrite(1, t);
		//Some examples of other functions you can use to send data.
		//Cayenne.celsiusWrite(1, 22.0);
		//Cayenne.luxWrite(2, 700);
		//Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
	}
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
