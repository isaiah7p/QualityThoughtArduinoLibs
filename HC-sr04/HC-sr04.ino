/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 3, TXPin = 1;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
BlynkTimer timer;

SoftwareSerial ss(RXPin, TXPin);
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a662fbb085fb428fb7453064856e8aff";

// Your WiFi credentials.
// Set password to "" for open networks.


char ssid[] = "Srujan";
char pass[] = "Sruj@n97";

//char ssid[] = "Quality Thought 605B";
//char pass[] = "roundtable";

// defines pins numbers
const int trigPin = 2;
const int echoPin = 0;
const int trigPin1 = 5;
const int echoPin1 = 4;
// defines variables
long duration;
int distance;
long duration1;
int distance1;
WidgetMap myMap(V1);
void setup() {
   
   Serial.begin(9600); // Starts the serial communication

  Blynk.begin(auth, ssid, pass);
  
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
pinMode(LED_BUILTIN, OUTPUT);

   timer.setInterval(1000L, getCoordinates);
 

}
void loop() {
   

   Blynk.run();
  timer.run();
//

  
  float lat = (gps.location.lat(), 7);
  float lon = (gps.location.lng(), 7);
Serial.println(lat);
Serial.println(lon);

delay(1000);
}
void getCoordinates()
{
  myMap.clear();
  
  float lat = (gps.location.lat(), 7);
  float lon = (gps.location.lng(), 7);
Serial.println(lat);
Serial.println(lon);
  myMap.location(1, lat, lon, "SMART BIN");
}
