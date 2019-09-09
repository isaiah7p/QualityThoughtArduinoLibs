#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONEWIRE_PIN 5
#define UPDATE_DELAY  5000

OneWire oneWire(ONEWIRE_PIN);
DallasTemperature sensors(&oneWire);

boolean TempSensorAvailable = false;

DeviceAddress TempSensor;
float tempC, tempF; // sensor values
int sensorNum = 100 ; // to tell sensors apart if you plan to log data from more than one 
int logNum = 0;  //log file counter

const char* ssid = "Quality Thought";     // Your local WiFi SSID (the network name you connect to)
const char* ssid_password ="roundtable";// "quality@testing123";  // YOur local SSID password
const char* s3endpoint = "iotdemoqtsatyam.s3.amazonaws.com"; // WARNING: S3 Bucket names must be unique across all AWS S3 buckets 
                        //qualitythoughtiot

WiFiClient client;

void setup() {

  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, ssid_password);
  Serial.println("SSID ::");
  Serial.println(ssid);
  Serial.print("Password:: ");
  
  Serial.print(ssid_password);

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

  sensors.begin();

  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" OneWire device(s).");

  // report parasite power requirements
  Serial.print("Parasite power: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  if (!sensors.getAddress(TempSensor, 0)) {
    Serial.println("No OneWire Device Found");
  } else {
    TempSensorAvailable = true;
    Serial.println("OneWire Device Found");
    sensors.setResolution(TempSensor, 12);
  }
}

void loop() {
  String logfile;
  sensors.requestTemperatures();          // Get temprature
  tempC = sensors.getTempC(TempSensor);   // save temprature
  tempF = DallasTemperature::toFahrenheit(tempC);
  
  Serial.print("Temp C: ");
  Serial.println(tempC);        // Serial print the C  temperature
  Serial.print("Temp F: ");
  Serial.print(tempF);  // Convert then Serial print the F  temperature
  Serial.println("");

  if (client.connect(s3endpoint, 80)) {    // Connect to the AWS S3 bucket endpoint
    Serial.print("Connected to: ");
    Serial.println( s3endpoint);
    String postStr = "TEMP F: ";              // Build the body text of the logfile. You can leave this empty if you prefer to log values to the file name instead of body
    postStr += String(tempF);
    postStr += " - TEMP C: ";
    postStr += String(tempC);
    // Format your log file name for ease of listing and importing
    // Example: sensor number-log data number-log value
    String logfileName = String(sensorNum) + "-" + String(logNum++) + "Temp: " + String(tempC);  
    Serial.println(logfileName); 

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
    delay(UPDATE_DELAY);  // Some delay
  }
}
