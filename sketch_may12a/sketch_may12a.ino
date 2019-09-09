#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            5         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

char ssid[] = "NETGEAR68";
char pass[] = "Quality@qt";

char auth[] = "26165288780344dcb3f8470e4dc4b9ea";        // write your auth code here
void setup()
{ 
Serial.begin(9600); 
  // Initialize device.
  dht.begin();
  
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  //DHT11.attach(5);      // connect pin 2 to the sensor
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);
     // start blynk server and connect to the cloud
 while (Blynk.connect() == false) {
    // Wait until connected
  }
}
  
void loop(){ 
  // delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
  }
 // int chk = DHT11.read();
  float temp ,humid ;
temp  = event.temperature;
humid = event.relative_humidity;
  
   Blynk.virtualWrite(1, temp);  // Write values to the app
  Blynk.virtualWrite(2, humid);
  //Serial.println(event.temperature);

  Blynk.run();
  //timer.run();

}
