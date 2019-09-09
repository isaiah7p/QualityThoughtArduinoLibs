// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

const int trigPin2 = 2;  //D4
const int echoPin2 = 0;  //D3
#define trigPin3 D5
#define echoPin3 D6

long duration1,duration2,distance2,distance3, RightSensor,LeftSensor;
// WiFi network info.
char ssid[] = "Srujan";
char wifiPassword[] = "Sruj@n97";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "335c61a0-f912-11e8-898f-c12a468aadce";
char password[] = "ff3b003ca67880b00fe543c20315d1e23f4c2a65";
char clientID[] = "a0907740-0040-11e9-810f-075d38a26cc9";

unsigned long lastMillis = 0;

void setup() {
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  Serial.begin(9600);
}

void loop() {
  Cayenne.loop();
SonarSensor(trigPin2, echoPin2);
RightSensor = distance2;
SonarSensor(trigPin3, echoPin3);
LeftSensor = distance3;
Serial.print(LeftSensor);
Serial.print(" - ");
Serial.println(RightSensor);
delay(200);
}

void SonarSensor( int , int )
{
  
digitalWrite( trigPin2 , LOW);
delayMicroseconds(2);

// Sets the trigPin2 on HIGH state for 10 micro seconds
digitalWrite( trigPin2 , HIGH);
delayMicroseconds(10);
digitalWrite( trigPin2 , LOW);

// Reads the echoPin2, returns the sound wave travel time in microseconds
duration1 = pulseIn(echoPin2, HIGH);

digitalWrite(trigPin3, LOW);
delayMicroseconds(2);

// Sets the trigPin3 on HIGH state for 10 micro seconds
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);

// Reads the echoPin3, returns the sound wave travel time in microseconds
duration2=  pulseIn(echoPin3, HIGH);

// Calculating the distance 1,2
distance2 = duration1*0.034/2 ;
distance3 = duration2*0.034/2 ;

}
// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  //Cayenne.virtualWrite(0, millis());
  Cayenne.virtualWrite(0, RightSensor);
  Cayenne.virtualWrite(1,LeftSensor);

  Cayenne.virtualWrite(2,17.4315278);
  Cayenne.virtualWrite(3,78.4380196);

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
