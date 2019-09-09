// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 14 // D5   // what digital pin we're connected to
#define ledPin 12 //D6
#define relay1 5  //D1
#define relay2 4  //D2
#define in1 3  //D9
#define in2 1  //D10

int val = 0;

int val2 = 0;
//relay1 relay2 in1 in2


// Uncomment whatever type you're 3using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

//
//
// ROBO India Blynk Board : 
//
// 1. Input Switch 1 : GPI0 03 (D9) 
// 2. Input Switch 2 : GPI0 01 (D10)
// 3. Output Relay 1 : GPI0 05 (D1) 
// 4. Output Relay 2 : GPI0 04 (D2) 
// 5. Output LED : GPI0 12 (D6) 
// 6. Temperature & Humidity Sensor DHT-11 : GPI0 14 (D5) 


// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  // relay2 in1 in2
  pinMode(ledPin,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(in1,INPUT);
  pinMode(in2,INPUT);
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
   delay(1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if(h>90){
    digitalWrite(ledPin,HIGH);
    digitalWrite(relay1,HIGH);
     Serial.print("Humidity is greater than 90  ");
    delay(500);
    digitalWrite(ledPin,LOW);
    digitalWrite(relay1,LOW);
    
    delay(500);
    }
  if(t>30){
     digitalWrite(ledPin,HIGH);
    digitalWrite(relay2,HIGH);
     Serial.print("temerature is greater than 30  ");
    delay(500);
    digitalWrite(ledPin,LOW);
    digitalWrite(relay2,LOW);
    delay(500);
    
    }
   
  val = digitalRead(in1);   // read the input pin
  digitalWrite(ledPin, val);  
     Serial.print("Led 1 Condition : ");
     Serial.print(val);
  val2 = digitalRead(in2);   // read the input pin
  digitalWrite(relay2, val2);
     Serial.print("Led 2 Condition  : ");
     Serial.print(val2);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  
}
