#include <CayenneMQTTESP8266.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define CAYENNE_PRINT Serial
// WiFi network info.
char ssid[] = "DustDevils";
char wifiPassword[] = "b4b3c69b4688!";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "3add4cb0-10a5-11e8-b797-8356759ccb0f";
char password[] = "c922f4963798746fcff3159cd65b0387a554445d";
char clientID[] = "2f6344b0-47ce-11e8-98f3-296704efce3e";

const char* mqtt_server = "192.168.2.6";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int threhold=50; 


unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup ");
 //FreqMeasure.begin();
  //setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.println("MQTT SERVER IP ");
  Serial.println(mqtt_server);
  
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
float heartRate = analogRead(A0);

    
   delay(100);
  

        Cayenne.virtualWrite(0,heartRate);
       // Cayenne.virtualWrite(2, spo2);
       // Cayenne.virtualWrite(1,heartRate );
        delay(250); 

          if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();

  if (now - lastMsg > 500) {
     lastMsg = now;

     String msg= "Critical Condition With Heart Raising";
   // msg= msg+ val;
   //if (val>threhold)
   //   msg="0: "+msg;
  //  else
  //    msg="1: "+msg;
     char message[58];
     msg.toCharArray(message,58);

     Serial.println(message);
  
     //publish sensor data to MQTT broker

      client.publish("icu/patient3", message);
  }
  
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}


void callback(char* topic, byte* payload, unsigned int length) 
{
} //end callback

void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ice/patient3";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("ice/patient3");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(6000);
    }
  }
} //end reconnect()


