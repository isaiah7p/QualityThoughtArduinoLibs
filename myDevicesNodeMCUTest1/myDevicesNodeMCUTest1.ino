// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <DHT.h>


// WiFi network info.
char ssid[] = "DustDevils";
char wifiPassword[] = "b4b3c69bb4b3c69b5267!";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "6fff5240-f05c-11e6-a971-4db18559717d";
char password[] = "4a5495303e20c8e904dab1862802bb32990cd994";
char clientID[] = "1f0dd000-0951-11e8-a2eb-7d0b45aada7b";



DHT dht(D2,DHT22);

void setup() {
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
}

void loop() {
	Cayenne.loop();

//	//Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
//	if (millis() - lastMillis > 10000) {
//		lastMillis = millis();
//		//Write data to Cayenne here. This example just sends the current uptime in milliseconds.
//		Cayenne.virtualWrite(0, lastMillis);
//		//Some examples of other functions you can use to send data.
//		//Cayenne.celsiusWrite(1, 22.0);
//		//Cayenne.luxWrite(2, 700);
//		//Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
//	}

float temp = dht.readTemperature(true); // Fare
float hum = dht.readHumidity();



Cayenne.virtualWrite(1,temp , TYPE_TEMPERATURE , UNIT_FAHRENHEIT );
Cayenne.virtualWrite(2,hum , TYPE_RELATIVE_HUMIDITY , UNIT_PERCENT );
Serial.println(temp);
Serial.println(hum);
}
CAYENNE_IN(0)
{
  digitalWrite(2,!getValue.asInt());
}
CAYENNE_IN(1)
{
  digitalWrite(2,!getValue.asInt());
}


//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
//CAYENNE_IN_DEFAULT()
//{
//	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
//	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
//}
