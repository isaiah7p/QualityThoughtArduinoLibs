// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

#define trigPin2 D3
#define echoPin2 D4
#define trigPin3 D5
#define echoPin3 D6
long duration1,duration2,distance2,distance3, RightSensor,LeftSensor;
// WiFi network info.
char ssid[] = "Srujan";
char wifiPassword[] = "Sruj@n97";
int dryLevel=0;
int wetLevel =0;
// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "335c61a0-f912-11e8-898f-c12a468aadce";
char password[] = "ff3b003ca67880b00fe543c20315d1e23f4c2a65";
char clientID[] = "a0907740-0040-11e9-810f-075d38a26cc9";

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

void loop() {
  Cayenne.loop();

   dryLevel = leftSonarSensor();
   wetLevel = rightSonarSensor();
 Cayenne.virtualWrite(0, dryLevel);
  Cayenne.virtualWrite(1,wetLevel);

Serial.print(dryLevel);
Serial.print(" - ");
Serial.println(wetLevel);
delay(200);
}

int leftSonarSensor()
{

digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
duration1 = pulseIn(echoPin2, HIGH);
distance2 = (duration1/2) / 29.1;
return distance2;
}

int rightSonarSensor()
{
digitalWrite(trigPin3, LOW);
delayMicroseconds(10);
digitalWrite(trigPin3, HIGH);
duration2=  pulseIn(echoPin3, HIGH);
distance3 = (duration2/2) / 29.1;

return distance3;
}
// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  //Cayenne.virtualWrite(0, millis());
  Cayenne.virtualWrite(0, dryLevel);
  Cayenne.virtualWrite(1,wetLevel);
  Serial.print(" Uploaded Data DryLevel :");
  Serial.print(dryLevel);
  Serial.print(" Uploaded Data WetLevel:");
  Serial.println(wetLevel);
  // Some examples of other functions you can use to send data.
  //Cayenne.celsiusWrite(1, 22.0);
  //Cayenne.luxWrite(2, 700);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
