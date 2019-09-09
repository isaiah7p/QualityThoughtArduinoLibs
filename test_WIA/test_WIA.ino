#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ArduinoHttpClient.h>

const char* ssid     = "Quality Thought 605B";
const char* password = "roundtable";

// get this from the wia dashboard. it should start with `d_sk`
const char* device_secret_key = "d_sk_oA4PUq6dXcMZfvtOQo8eSZfp";

char server[] = "api.wia.io";
char path[] = "/v1/events";
int port = 80;

WiFiClient client;
int status = WL_IDLE_STATUS;


StaticJsonDocument<200> jsonBuffer;
JsonObject root = jsonBuffer.to<JsonObject>();

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  WiFi.begin(ssid, password);
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  // attempt to connect to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // Connect to WPA/WPA2 network. Change this line if using open or WEP  network:
    // wait 5 seconds for connection:
    delay(5000);
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Connected");
}

void loop() {
  root["name"] = "hello-wia";
  postToWia(root);
  delay(10000);
}

// Adds the correct headers for HTTP and sends Data to Wia
void postToWia(JsonObject& data) {
  String dataStr = "";
  serializeJson(data, dataStr);
  HttpClient(client, server, port).beginRequest();
  HttpClient(client, server, port).post(path);
  HttpClient(client, server, port).sendHeader("Content-Type", "application/json");
  HttpClient(client, server, port).sendHeader("Content-Length", dataStr.length());
  HttpClient(client, server, port).sendHeader("Authorization", "Bearer "  + String(device_secret_key));
  HttpClient(client, server, port).beginBody();
  HttpClient(client, server, port).print(dataStr);
  HttpClient(client, server, port).endRequest();
}
