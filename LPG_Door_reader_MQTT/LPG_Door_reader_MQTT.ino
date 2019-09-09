/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>           //Servo library
 
Servo servo_test; 
// Update these with values suitable for your network.

const char* ssid = "Quality Thought 605B";
const char* password = "roundtable";
const char* mqtt_server = "192.168.1.38";

//int ENA = 15; //D8;
//int IN1 = 12; //D6;
//int IN2 = 13; //D7;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
//const int buzzer = 3; 
const int sensor = 4;
int fanPin = 12;
int piezoPin  = 5 ;

int servoPin  = 2;


float sensorVoltage; 
  float sensorValue;

int state; // 0 close - 1 open wwitch


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   
      servo_test.write(0); 
      // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
int angle = 0; 
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  servo_test.attach(servoPin); 
  servo_test.write(0);
//  pinMode(ENA, OUTPUT);
//  pinMode(IN1, OUTPUT);
//  pinMode(IN2, OUTPUT);
  pinMode(fanPin, OUTPUT);
  
  pinMode(sensor, INPUT_PULLUP);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
    
  sensorValue = analogRead(A0);
  sensorVoltage = sensorValue/1024*5.0;
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  
  
  if(sensorVoltage>1){
      
    snprintf (msg, 75, "Gas Leakage Detected ","");
    
    client.publish("gas", msg);
    
     
    Serial.print("Publish message: ");
    for(angle = 0; angle < 180; angle += 10)    // command to move from 0 degrees to 180 degrees 
    {                                  
    servo_test.write(angle);                 //command to rotate the servo to the specified angle
    delay(15);                       
    } 
    
// 
//    testOne();   
//    delay(500);   
//    testTwo();   
//    delay(500);
    Serial.println(msg);
    delay(20000);
    sensorVoltage=0;
    // buzzer code : 
   
    }
    else{

      }

  
  delay(1000);
  state = digitalRead(sensor);
  
  if (state == HIGH){
  
    snprintf (msg, 75, "Intruder Detected at Front Door", "");
    Serial.print("Publish message: ");
    
    tone(piezoPin, 1000, 500);
     delay(1000);
    noTone(piezoPin); 
       
    Serial.println(msg);
    client.publish("intruder", msg);
  }
  else{
   // noTone(buzzer);
  }
  delay(200);
  
   
//servo_test.write(0);
    
 // }
 
}

//
//void testOne() {
//// turn on motor
//digitalWrite(ENA, HIGH);  // set speed to 200 out of possible range 0~255
//digitalWrite(IN1, HIGH);
//digitalWrite(IN2, LOW);
//
//delay(1000); // now change motor directions
//
//digitalWrite(IN1, LOW);
//digitalWrite(IN2, HIGH);
//
//delay(1000); // now turn off motors
//
//digitalWrite(IN1, LOW);
//digitalWrite(IN2, LOW);
//}
//
//// this function will run the motors across the range of possible speeds
//// note that maximum speed is determined by the motor itself and the operating voltage
//// the PWM values sent by analogWrite() are fractions of the maximum speed possible by your hardware
//
//void testTwo() {
//
//// turn on motors
//digitalWrite(IN1, HIGH);
//digitalWrite(IN2, LOW);
//
//// accelerate from zero to maximum speed
//for (int i = 0; i < 256; i++)
//  {
//    analogWrite(ENA, i);
//    delay(50);
//   }
//
//// decelerate from maximum speed to zero
//for (int i = 255; i >= 0; --i)
//    {
//      analogWrite(ENA, i);
//      delay(50);
//     }
//
//// now turn off motors
//digitalWrite(IN1, LOW);
//digitalWrite(IN2, LOW);
//}
