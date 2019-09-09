#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "Quality Thought";
const char* password = "roundtable";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";

int LEDPin = 5;
int LED1Pin = 4;

void setup(void){
  //the HTML of the web page
  page = "<h1> IOT Students Quality thought</h1><p><a href=\"LEDOn\"><button>ON </button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p><p><a href=\"LED1On\"><button>LED 1 ON </button></a>&nbsp;<a href=\"LED1Off\"><button>LED 1 OFF</button></a></p>";
  //make the LED pin output and initially turned off
   pinMode(LEDPin, OUTPUT);
   pinMode(LED1Pin, OUTPUT);
   
   digitalWrite(LEDPin, LOW);
   digitalWrite(LED1Pin, LOW);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); // begin WiFi connection
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(LEDPin, LOW);
    delay(1000); 
  });
  server.on("/LED1On", [](){
    server.send(200, "text/html", page);
    digitalWrite(LED1Pin, HIGH);
    delay(1000);
  });
  server.on("/LED1Off", [](){
    server.send(200, "text/html", page);
    digitalWrite(LED1Pin, LOW);
    delay(1000); 
  });
  
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}
