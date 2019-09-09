// 
/*
This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.

The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. If you have not already installed the ESP8266 Board Package install it using the instructions here: https://github.com/esp8266/Arduino#installing-with-boards-manager.
2. Select your ESP8266 board from the Tools menu.
3. Set the Cayenne authentication info to match the authentication info from the Dashboard.
4. Set the network name and password.
5. Compile and upload the sketch.
6. A temporary widget will be automatically generated in the Cayenne Dashboard. To make the widget permanent click the plus sign on the widget.
*/
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "Quality Thought";
char wifiPassword[] = "roundtable";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "189af6f0-d74e-11e8-810f-075d38a26cc9";
char password[] = "ff80f657ba1b4cb9d2cee4392127651f6453e78a";
char clientID[] = "85126bf0-e0f0-11e8-8e60-53d8c8eabc71";
String content = "";


void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  // Serial serial = new Serial(this,Serial.list()[0],115200);
   
    Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() { // run over and over
  Cayenne.loop();
  

  
//  if (Serial.available()) {
//  Serial.write(Serial.read());
//  }
}

CAYENNE_OUT_DEFAULT() 
{
   
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
//String content = "75.00,30.00,28.33,30.10,95295.00,514.00,631.00,205.00,3.02,15.94";
//String c_str=""; 

if (Serial.available()) {
  while (Serial.available()) {
    content += Serial.read();
  }
}
float data[10]={0,0,0,0,0,0,0,0,0,0}; //The results will be stored here
for(int i = 0; i < 10; i++){
  int index = content.indexOf(","); //We find the next comma
  data[i] = atol(content.substring(0,index).c_str()); //Extract the number

  content = content.substring(index+1); //Remove the number from the string
  Serial.println(data[i]);
  Cayenne.virtualWrite(i, data[i]);
//delay(6000);
}
content = "";
delay(1000);
  // Some examples of other functions you can use to send data.
  //Cayenne.celsiusWrite(0, 100);
  //Cayenne.luxWrite(1, 35);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
