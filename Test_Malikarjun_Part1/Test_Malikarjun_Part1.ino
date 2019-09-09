/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
//char ssid[] = "Srujan";
//char wifiPassword[] = "Sruj@n97";

char ssid[] = "Quality Thought 605B";
char wifiPassword[] = "roundtable";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "f3622810-65d0-11e9-bdb5-dfd20f02ea3f";
char password[] = "97009ce3653d6157221f2af80cfabdae29ef63fe";
char clientID[] = "3723e3e0-65d1-11e9-bdb5-dfd20f02ea3f";

// defines pins numbers
const int trigPin = 5;
const int echoPin = 4;

// defines variables
long duration;
int distance;

void setup() {
   Serial.begin(9600); // Starts the serial communication
   Cayenne.begin(username, password, clientID, ssid, wifiPassword);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

pinMode(LED_BUILTIN, OUTPUT);

}
void loop() {
   Cayenne.loop();
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

delay(1000);

  Cayenne.virtualWrite(0,distance);
 
  Cayenne.virtualWrite(2,17.4315278);
  Cayenne.virtualWrite(3,78.4380196);

delay(1000);
}

CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  //Cayenne.virtualWrite(0, millis());
  Cayenne.virtualWrite(0,distance);
 
  Cayenne.virtualWrite(2,17.4315278);
  Cayenne.virtualWrite(3,78.4380196);

  // Some examples of other functions you can use to send data.
  //Cayenne.celsiusWrite(1, 22.0);
  //Cayenne.luxWrite(2, 700);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
