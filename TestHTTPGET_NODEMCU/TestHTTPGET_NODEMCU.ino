#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "QUALITY THOUGHTS";
const char* password = "9963799240";
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
 
}
 
void loop() {
 Serial.println("Test Loop"); 
 // get the data  
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("https://qtcutie.mybluemix.net/mytest?temp=35");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println(httpCode); 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(2000);    //Send a request every 30 seconds
 
}
