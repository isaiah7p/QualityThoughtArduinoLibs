#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#define DHTPIN            4         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 

DHT_Unified dht(DHTPIN, DHTTYPE);
//  

// Update these with values suitable for your network.
const char* ssid = "Quality Thought";
const char* password = "littlebox";
const char* mqtt_server = "192.168.1.33";
uint32_t delayMS;
int logNum = 0;  //log file counter
float tempC, tempF , humidity; // sensor 

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int countVal = 0;
int threhold=50; // you might need to adjust this value to define light on/off status
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

void callback(char* topic, byte* payload, unsigned int length) 
{
} //end callback

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

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.println("MQTT SERVER IP ");
  Serial.println(mqtt_server);
   
  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
    tempC = 0;
  tempF = 0;
  humidity = 0;
  
}

void loop() {

  //int bpm = analogRead(A0);

  String logfile;

  
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    tempC = event.temperature;
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
    humidity = event.relative_humidity;
  }
  
  Serial.print("Temp C: ");
  Serial.println(tempC);        // Serial print the C  temperature
  Serial.print("Temp F: ");
  Serial.print(tempF);  // Convert then Serial print the F  temperature
  Serial.println("");
   //Serial.println("Heart Rate ::: ");
  // int hr = bpm/5.45;
  //Serial.println(hr);
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();

  if (now - lastMsg > 500) {
     lastMsg = now;
  
     String msg= " Room Temperature :: ";
    msg= msg + tempC;
     String msg1= " Room Humidity :: ";
    msg1= msg1 + humidity;
   //if (val>threhold)
   //   msg="0: "+msg;
  //  else
  //    msg="1: "+msg;
     char message[58];
     msg.toCharArray(message,58);

      char message1[58];
     msg1.toCharArray(message1,58);


  
     //publish sensor data to MQTT broker
     // if(hr > 110 ){
      client.publish("room/temp", message);
       client.publish("room/humidity", message1);
           Serial.println(message);
           Serial.println(message1);
            //  countVal = 0;
      //}
  }
   countVal++;

   delay(3000); // half seconds delay ....... 
}

