
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <SimpleTimer.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();


const int MPU_addr=0x68;
int16_t AcX, AcY, AcZ, TmP,GyX,GyY,GyZ;
float AcX_calc, AcY_calc, AcZ_calc;
uint32_t lastTime;


const char* ssid = "Quality Thought 605B";
const char* password = "roundtable";
const char* mqtt_server = "192.168.1.17";


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50],msg1[50];
int value = 0;


int UpperThreshold = 518;
int LowerThreshold = 490;
    int reading = 0;
    float BPM = 0.0;
    bool IgnoreReading = false;
    bool FirstPulseDetected = false;
    unsigned long FirstPulseTime = 0;
    unsigned long SecondPulseTime = 0;
    unsigned long PulseInterval = 0;

    void setup(){
    Serial.begin(115200);
       
        mlx.begin();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
    }

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


    void loop(){
 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
    
//  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
//  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
//  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
//  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
//      
  float ObjectTemp = mlx.readObjectTempF();
       
    snprintf (msg1, 75, "%lf", ObjectTemp);
    
    Serial.print("Object temperature message: ");
    Serial.println(msg1);
    client.publish("temp", msg1);
    
 Serial.print("ObjectTemp = "); Serial.print(ObjectTemp); 
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
      delay(200);
      BPM = (1.0/PulseInterval) * 60.0 * 1000;
       // uncomment these lines in case you want to view the various values in the console.....
      /*Serial.print(reading);
      Serial.print("\t");
      Serial.print(PulseInterval);
      Serial.print("\t");*/
      Serial.print(BPM);
      Serial.println(" BPM");
      //BPM  = constrain(BPM, 54, 200);
        
    snprintf (msg, 75, "%lf", BPM);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("heartrate", msg);

    if(BPM>110){
    
    
    Serial.print("Publish message: ");
    Serial.println();
    client.publish("Alarm", "Alarm");
    }
    if(ObjectTemp>104){
    
    
    Serial.print("Publish message: ");
    Serial.println();
    client.publish("Alarm", "Alarm");
    }
      Serial.flush();
    }
    
