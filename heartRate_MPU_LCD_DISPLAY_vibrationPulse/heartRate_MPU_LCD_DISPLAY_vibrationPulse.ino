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
#include <Wire.h>
#include <SimpleTimer.h>

const int MPU_addr=0x68;
int16_t AcX, AcY, AcZ, TmP,GyX,GyY,GyZ;
float AcX_calc, AcY_calc, AcZ_calc;
uint32_t lastTime;


// Update these with values suitable for your network.

const char* ssid = "Quality Thought 605B";
const char* password = "roundtable";
const char* mqtt_server = "192.168.1.87";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

#define LED_PIN 14
#define BUTTON_PIN 12

int UpperThreshold = 518;
int LowerThreshold = 490;
    int reading = 0;
    float BPM = 0.0;
    bool IgnoreReading = false;
    bool FirstPulseDetected = false;
    unsigned long FirstPulseTime = 0;
    unsigned long SecondPulseTime = 0;
    unsigned long PulseInterval = 0;



#define DEMO_DURATION 3000
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 1;



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
    
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
  Serial.println("Message Received from Raspberry Pi ");
   Serial.println((char)payload[0]);
  

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

void setup() {
       // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);


  Wire.begin(4,5);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}




void check_imu(){
  readIMU();
  Serial.print("AcX: "); Serial.print(AcX); Serial.print("g | AcY: "); Serial.print(AcY); Serial.print("g | AcZ: "); Serial.print(AcZ);
  Serial.println("g");
  if(abs(AcX_calc)> 22000 || abs(AcY)> 22000|| abs(AcZ) > 27000){
    Serial.println("Fall detected");
    int hr =   getHeartPulse();
    if(hr>170){
      
      }
   
    delay(50);
  }
  
}



void loop() {
      
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

    reading = analogRead(A0); 
      if(reading > UpperThreshold && IgnoreReading == false){
        if(FirstPulseDetected == false){
          FirstPulseTime = millis();
          FirstPulseDetected = true;
        }
        else{
          SecondPulseTime = millis();
          PulseInterval = SecondPulseTime - FirstPulseTime;
          FirstPulseTime = SecondPulseTime;
        }
        IgnoreReading = true;
      }
      if(reading < LowerThreshold){
        IgnoreReading = false;
      }  

      BPM = (1.0/PulseInterval) * 60.0 * 1000;
      Serial.println("Fall detected");
     // BPM

  readIMU();
  Serial.print("AcX: "); Serial.print(AcX); Serial.print("g | AcY: "); Serial.print(AcY); Serial.print("g | AcZ: "); Serial.print(AcZ);
  Serial.println("g");
  if(abs(AcX_calc)> 22000 || abs(AcY)> 22000|| abs(AcZ) > 27000){
    Serial.println("Fall detected");
    
    if(BPM>170){
      
      
      // heartrate
       client.publish("fallstatus", "Fall Detected");
      }
   
    delay(50);
    } 
    
//  long now = millis();
//  if (now - lastMsg > 2000) {
//    lastMsg = now;
//    ++value;

       snprintf (msg, 75, "Heart Rate %ld", BPM);
        Serial.print("Publish message: ");
        Serial.println(msg);
    
    // heartrate
    
        client.publish("heartrate", msg);
    // heartrate
    
    //client.publish("outTopic", msg);
//  }

  
}

int getHeartPulse(){

    reading = analogRead(0); 
      if(reading > UpperThreshold && IgnoreReading == false){
        if(FirstPulseDetected == false){
          FirstPulseTime = millis();
          FirstPulseDetected = true;
        }
        else{
          SecondPulseTime = millis();
          PulseInterval = SecondPulseTime - FirstPulseTime;
          FirstPulseTime = SecondPulseTime;
        }
        IgnoreReading = true;
      }
      if(reading < LowerThreshold){
        IgnoreReading = false;
      }  

      BPM = (1.0/PulseInterval) * 60.0 * 1000;
       // uncomment these lines in case you want to view the various values in the console.....
      /*Serial.print(reading);
      Serial.print("\t");
      Serial.print(PulseInterval);
      Serial.print("\t");*/
      Serial.print(BPM);
      Serial.println(" BPM");
      Serial.flush();
      return BPM;
  
  }

void readIMU(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  TmP=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

void blink_led(int times){
  for(int i=0;i<times;i++){
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);
  }
}
void alarm(){
  digitalWrite(LED_PIN, HIGH);
  Serial.println("Alarm sent!");
  //Cayenne.virtualWrite(1,2);
  delay(100);
  //Cayenne.virtualWrite(1,0);
  digitalWrite(LED_PIN, LOW);
}
