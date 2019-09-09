#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Quality Thought 605B";                   // wifi ssid
const char* password =  "roundtable";         // wifi password
const char* mqttServer = "192.168.1.86";    // IP adress Raspberry Pi
const int mqttPort = 1883;
//const char* mqttUser = "username";      // if you don't have MQTT Username, no need input
//const char* mqttPassword = "12345678";  // if you don't have MQTT Password, no need input

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(D1,OUTPUT);
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  //client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

  //  if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");

  //  } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }

//  client.publish("esp8266", "Hello Raspberry Pi");
//  client.subscribe("esp8266");


void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");

}

void loop() {
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1000);
//if(analogRead(A0)>700)
//{
  digitalWrite(D1,HIGH);
  delay(5000);
  digitalWrite(D1,LOW);
  delay(2000);
   client.publish("esp8266", "Hello Raspberry Pi");
   //client.subscribe("esp8266");
   delay(300);
   client.loop();
//}
}
