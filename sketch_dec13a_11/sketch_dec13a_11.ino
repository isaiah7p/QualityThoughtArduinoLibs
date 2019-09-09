//#define CAYENNE_PRINT Serial   // Comment this out to disable prints and save space
#include <SPI.h>
#include <SimpleTimer.h>
//#include <CayenneEthernet.h> //when using W5100
///*
// with the ESP8266 module
#include "CayenneDefines.h"
#include "BlynkSimpleEsp8266.h"
#include "CayenneWiFiClient.h"
// Your network name and password.
char ssid[] = "joelgloria";
char password[] = "b4b3c69b5267!";
//*/

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "xxxx";

SimpleTimer timer;

// for DHT22
#include <DHT.h>
// DHT22 temp & vochtmeter
#define DHTPIN D6        // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

// for HC-SR04
#define echoPin D4 // Echo Pin
#define trigPin D5 // Trigger Pin
float h, t, f; //declare variable used in HC-SR04

// establish variables for duration of the ping, 
// and the distance result in inches and centimeters:
long duration, distance, distance_new, logecho; // Duration used to calculate distance

void setup() {
  //Cayenne.begin(token); //with W5100
  Cayenne.begin(token, ssid, password); //with ESP8266
  Serial.begin(115200);
  Serial.println("info: sketch_Distance_Cayenne");
  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  timer.setInterval(60000, RepeatTask);
  timer.setInterval(6000, RepeatEcho);

  // initialise DHT
  Serial.println("DHTxx begin!\n");
  dht.begin();
}


CAYENNE_OUT(V3) {
  Cayenne.virtualWrite(V3,logecho); // virtualpin 3 plus distance
}

CAYENNE_OUT(V4) {
  Cayenne.virtualWrite(V4,distance); // virtualpin 4 plus distance
}

CAYENNE_OUT(V5) {
  Cayenne.virtualWrite(V5,t); // virtualpin 5 (temperature)
}

CAYENNE_OUT(V6) {
  Cayenne.virtualWrite(V6,h); // virtualpin 6 (huminity)
}

void loop() {
  Cayenne.run(); // Initiates Blynk
  timer.run();   // Initiates SimpleTimer
}
