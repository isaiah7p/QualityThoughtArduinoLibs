#include "DHT.h"

#define DHTPIN 14     // what digital pin we're connected to

int inPin = 3;
int ledPin  =  12 ;
int relay1 = 5;
int relay2  = 4;
int val = 0;
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("in setup method ========");

  dht.begin();
  pinMode(inPin , INPUT_PULLUP);

  pinMode(ledPin , OUTPUT);

  pinMode(relay1 , OUTPUT);
  pinMode(relay2 , OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

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

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");



  if (t > 29) {

    Serial.println("in input is HIGH  ");

    digitalWrite(relay1, HIGH);


  } else {

    Serial.println("in input is LOW   ");

    digitalWrite(relay1, LOW);

  }


}
