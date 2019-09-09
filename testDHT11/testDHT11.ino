#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin 5  //gpio0
DHT dht(dht_dpin, DHTTYPE); 
#define led_ext 4 // led output pin
void setup(void)
{ 
  
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humidity and temperature\n\n");
  delay(700);
  pinMode(led_ext, OUTPUT);
} 
void loop() { 
    float h = dht.readHumidity();
    float t = dht.readTemperature(); 
            if(h>90){
              digitalWrite(led_ext, HIGH);   // turn the LED on (HIGH is the voltage level)
              delay(100);                       // wait for a second
              digitalWrite(led_ext, LOW);    // turn the LED off by making the voltage LOW
              delay(100);    
              
              }
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
  delay(800);
}

