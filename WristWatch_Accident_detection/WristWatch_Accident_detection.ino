#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
/********* WiFi Access Point ***********/
#define WLAN_SSID       "Quality Thought 605B"
#define WLAN_PASS       "roundtable"
#define MQTT_SERVER      "192.168.1.56"  // MQTT Broker address
#define MQTT_PORT         1883
#define MQTT_USERNAME    ""
#define MQTT_PASSWORD    ""
#define led_pin 4
#define sensor_input A0
int percent;  
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

Adafruit_MQTT_Client mqtt (&client, MQTT_SERVER, MQTT_PORT);

Adafruit_MQTT_Publish pi_led = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "pulse");
Adafruit_MQTT_Publish alarm_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "alarm");
// Setup a feed called 'esp8266_led' for subscribing to changes.
Adafruit_MQTT_Subscribe esp8266_led = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "alarm");
/********* Sketch Code ************/
void MQTT_connect();
void setup() {

  pinMode(sensor_input, INPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(115200);
  delay(100);
  Serial.println(F("RPi-ESP-MQTT"));
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Setup MQTT subscription for esp8266_led feed.
  mqtt.subscribe(&esp8266_led);
}
uint32_t x = 0;
void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  int last_sensor_data = analogRead(sensor_input);
  MQTT_connect();
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
  // Here its read the subscription
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription())) {
     Serial.println((char *)esp8266_led.lastread);
    if (subscription == &esp8266_led) {
      //Serial.print(F("Got: "));
     Serial.println((char *)esp8266_led.lastread);
      char *data = (char *)esp8266_led.lastread;
      if (strncmp(data, "ON", 2) == 0)
      {
        Serial.println("Vibration Pulse Detected  ");
        digitalWrite(led_pin, HIGH);
        delay(1000);
        digitalWrite(led_pin, LOW);
        Serial.println("High");
      }
      else if (strncmp(data, "OFF", 3) == 0)
      {
        digitalWrite(led_pin, LOW);
        Serial.println("low");
      }
    }
  }
  delay(1000);
  //Publish Sensor data to RPi as its value varies and print on Serial Monitor
  int current_sensor_data = analogRead(sensor_input);
  percent = (int) ((current_sensor_data * 100) / 1010);
//percent = 190;
  if (percent > 180)
  {
  digitalWrite(led_pin, HIGH);
  delay(1000);
  digitalWrite(led_pin, LOW);
  delay(1000);
   alarm_pub.publish("ON");
  }
  if (percent != last_sensor_data)
  {
    pi_led.publish(percent);
   
   // Serial.println(percent);
  }
}
// Function to connect and reconnect as necessary to the MQTT server.
void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
