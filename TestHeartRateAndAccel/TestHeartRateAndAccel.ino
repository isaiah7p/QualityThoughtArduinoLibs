// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 
#include <Wire.h>
#include <SimpleTimer.h>

const int MPU_addr=0x68;
int16_t AcX, AcY, AcZ, TmP,GyX,GyY,GyZ;
float AcX_calc, AcY_calc, AcZ_calc;
uint32_t lastTime;

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "Quality Thought 605B";
char wifiPassword[] = "roundtable";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "6fff5240-f05c-11e6-a971-4db18559717d";
char password[] = "4a5495303e20c8e904dab1862802bb32990cd994";
char clientID[] = "45994c70-5506-11e9-8da4-359d3972629e";

#define LED_PIN 14
#define BUTTON_PIN 12

void check_imu(){
  readIMU();
  Serial.print("AcX: "); Serial.print(AcX); Serial.print("g | AcY: "); Serial.print(AcY); Serial.print("g | AcZ: "); Serial.print(AcZ);
  Serial.println("g");
  if(abs(AcX_calc)> 22000 || abs(AcY)> 22000|| abs(AcZ) > 27000){
    Serial.println("Fall detected");
    int button_val = 1;
    lastTime = millis();
    button_val = digitalRead(BUTTON_PIN);
    while(millis()-lastTime<5000){
      digitalWrite(LED_PIN, HIGH);
      button_val = digitalRead(BUTTON_PIN);
      delay(10); //Debounce
      Serial.println(button_val);
      if(!button_val) break;
    }
    if(!button_val){
      Serial.println("Didn't do anything, button was pressed");
      digitalWrite(LED_PIN, LOW);
      delay(200);
    }
    else{
      alarm();
    }
    delay(50);
  }
  
}

void setup() {
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
  Wire.begin(4,5);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);
  Serial.println("Wrote to IMU");
  
}

void loop() {
  int button_state = digitalRead(BUTTON_PIN);
  if(!button_state){
    alarm();
    delay(500);
  }
  Cayenne.loop();
  check_imu();
  if(millis()>(pow(2,32)-5000)){
    ESP.reset();
  }
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
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
  Cayenne.virtualWrite(1,2);
  delay(100);
  Cayenne.virtualWrite(1,0);
  digitalWrite(LED_PIN, LOW);
}
