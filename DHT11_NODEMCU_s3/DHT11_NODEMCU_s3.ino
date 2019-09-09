// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#define DHTPIN            5  // Pin which is connected to the DHT sensor D1 

// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
int logNum = 0;  //log file counter
float tempC, tempF , humidity; // sensor values
const char* ssid = "Quality Thought";             // Your local WiFi SSID (the network name you connect to)
const char* ssid_password = "roundtable";  // YOur local SSID password
const char* s3endpoint = "iotdenoqt.s3.amazonaws.com"; // WARNING: S3 Bucket names must be unique across all AWS S3 buckets 
WiFiClient client;
int ledPin = 4;
void setup() {
  Serial.begin(9600); 
  // WIFI Connection 
  delay(10);
 pinMode(ledPin,OUTPUT);
  WiFi.begin(ssid, ssid_password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  
  
  
  // Initialize device.
  
   
  
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

  //tempC = 
  Serial.print("Temp C: ");
  Serial.println(tempC);        // Serial print the C  temperature
  Serial.print("Temp F: ");
  Serial.print(tempF);  // Convert then Serial print the F  temperature
  Serial.println("");


  
  if (client.connect(s3endpoint, 80)) {    // Connect to the AWS S3 bucket endpoint
    Serial.print("Connected to: ");
    Serial.println( s3endpoint);
    String postStr = "TEMP C: ";              // Build the body text of the logfile. You can leave this empty if you prefer to log values to the file name instead of body
    postStr += String(tempC);
    postStr += " - Humidity : ";
    postStr += String(humidity);
    // Format your log file name for ease of listing and importing
    // Example: sensor number-log data number-log value
    String logfileName = "QualityThougt@IOT" + String(logNum++) + "TEMP:" + String(tempC)+ "HUMIDITY:" +String(humidity)+".txt";  
    Serial.println(logfileName); 
    String htmlFile = "<!DOCTYPE html><html> <script src="https://ajax.googleapis.com/ajax/libs/angularjs/1.6.9/angular.min.js"></script> <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css"><body> <script>var app=angular.module("myShoppingList",[]);app.controller("myCtrl",function($scope){$scope.products=[{"Name":"Temp","Value":/"+String(tempC)+/"},{"Name":"Humidity","Value":32},{"Name":"Density","Value":21}];$scope.addItem=function(){$scope.errortext="";if(!$scope.addMe){return;} if($scope.products.indexOf($scope.addMe)==-1){$scope.products.push($scope.addMe);}else{$scope.errortext="The item is already in your shopping list.";}} $scope.removeItem=function(x){$scope.errortext="";$scope.products.splice(x,1);}});</script> <div ng-app="myShoppingList" ng-cloak ng-controller="myCtrl" class="w3-card-2 w3-margin" style="max-width:400px;"> <header class="w3-container w3-light-grey w3-padding-16"><h3>IOT Sensor Data</h3> </header><ul class="w3-ul"><li ng-repeat="x in products" class="w3-padding-16">{{x.Name}} : {{x.Value}}</li></ul><div class="w3-container w3-light-grey w3-padding-16"><p class="w3-text-red">{{errortext}}</p></div></div></body></html>"
    /* Construct the PUT URL. Example:
      
      PUT /somelogfile.txt HTTP/1.1
      Host: somebucket.s3.amazonaws.com
      Cache-Control: no-cache

      some body text
    */
    client.print("PUT /"); client.print(logfileName); client.print(" HTTP/1.1\n");
    client.print("Host: "); client.print(s3endpoint); client.print("\n"); 
    client.print("Cache-Control: no-cache\n");
    client.print("Content-Length: "); client.print(postStr.length()); client.print("\n\n");
    client.print(postStr); // body text
    Serial.println("Upload Done ...");
    client.stop();

    Serial.println("Waiting...");
    delay(2000);  // Some delay9
  }
}
