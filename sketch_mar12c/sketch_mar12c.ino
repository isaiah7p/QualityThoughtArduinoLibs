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

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a662fbb085fb428fb7453064856e8aff";

// Your WiFi credentials.
// Set password to "" for open networks.


char ssid[] = "Srujan";
char pass[] = "Sruj@n97";

//char ssid[] = "Quality Thought 605B";
//char pass[] = "roundtable";

double flat = (17.4570034);
double flon = (78.4477807);
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

  
 

}
void loop() {
   Blynk.run();

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
///

digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echoPin1, HIGH);
// Calculating the distance
distance1= duration1*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance1);


 Blynk.virtualWrite(V5, constrain(distance,5,40));
  Blynk.virtualWrite(V6, constrain(distance1, 5, 40));
  

  myMap.clear();
  myMap.location(0, flat, flon, "Smart Bin");
  
Serial.println(flat);
Serial.println(flon);


delay(1000);
}
