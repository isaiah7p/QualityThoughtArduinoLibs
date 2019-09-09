
// WiFi Definitions
const char* ssid = "Esp8266TestNet";
const char* password = "Esp8266Test"; // has to be longer than 7 chars  

void setup() {
  // put your setup code here, to run once:
WiFi.mode(WIFI_AP);
WiFi.softAP(ssid, password, 1, 1); 

}


void loop() {
 // Check of client has connected
 WiFiClient client = server.available();
 if(!client) {
   return;
 }
 // Read the request line
 String request = client.readStringUntil('\r');
 Serial.println(request);
 client.flush();
 // Match request
 if(request.indexOf("/led/on") != -1) {
    digitalWrite(ledPin, HIGH);
    value = "on";
 } else if (request.indexOf("/led/off") != -1) {
    digitalWrite(ledPin, LOW);
     value = "off";
 }
 client.flush();
 // JSON response
 String s = "HTTP/1.1 200 OK\r\n";
 s += "Content-Type: application/json\r\n\r\n";
 s += "{\"data\":{\"message\":\"success\",\"value\":\"";
 s += value;
 s += "\"}}\r\n";
 s += "\n";
 // Send the response to the client
 client.print(s);
 delay(1);
 Serial.println("Client disconnected");
}
