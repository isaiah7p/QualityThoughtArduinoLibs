#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
 

const char* ssid = "joelgloria";
const char* password = "b4b3c69b";

char* topic = "madmaxian/test";
char* server = "192.168.2.2";  // raspberry pi address 

// Callback function header
void callback(char* topic, byte* temperatureSensor, unsigned int length);
WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

void callback(char* topic, byte* temperatureSensor, unsigned int length) {
  // handle message arrived
}


String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}

void setup() {
  Serial.begin(115200);
  delay(10);
   mlx.begin();  

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Generate client name based on MAC address and last 8 bits of microsecond counter
  String clientName;
  clientName += "esp8266-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);
  clientName += "-";
  clientName += String(micros() & 0xff, 16);

  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.print(" as ");
  Serial.println(clientName);
  
  if (client.connect((char*) clientName.c_str())) {
    Serial.println("Connected to MQTT broker");
    Serial.print("Topic is: ");
    Serial.println(topic);
    
    if (client.publish(topic, "hello from nodemcu")) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }
  }
  else {
    Serial.println("MQTT connect failed");
    Serial.println("Will reset and try again...");
    abort();
  }
}

void loop() {
  static int counter = 0;
  
  String payload = "{\"micros\":";
  payload += micros();
  payload += ",\"counter\":";
  payload += counter;
  payload += "}";

 Serial.print("*C\tObject = "); 
  Serial.print(mlx.readObjectTempC()); 
  Serial.println("*C");

  Serial.println();
  delay(1000);

  String temperatureSensor = "{\"temperature\":";
  temperatureSensor += mlx.readObjectTempC();
  temperatureSensor += ",\"°C \":";
  temperatureSensor += "}";

  
  
  if (client.connected()){
    Serial.print("Sending temperatureSensor date : ");
    Serial.println(temperatureSensor);
    
    if (client.publish(topic, (char*) temperatureSensor.c_str())) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }
  }
  ++counter;
  delay(5000);
}
