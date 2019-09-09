#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
char ssid[] = "Quality Thought";
char wifiPassword[] = "roundtable";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "189af6f0-d74e-11e8-810f-075d38a26cc9";
char password[] = "ff80f657ba1b4cb9d2cee4392127651f6453e78a";
char clientID[] = "85126bf0-e0f0-11e8-8e60-53d8c8eabc71";
String content = "";



void setup() {
  Serial.begin(115200);
//  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
   
}


void loop() {
  // Cayenne.loop();
  float array[10];
  String content = "";
if (Serial.available()) {
  while (Serial.available()<10) {
    content += Serial.read();
  }
}
float data[16]; //The results will be stored here
for(int i = 0; i < 16; i++){
  int index = content.indexOf(","); //We find the next comma
  data[i] = atol(content.substring(0,index).c_str()); //Extract the number
  content = content.substring(index+1); //Remove the number from the string
}
  //delay(1000);
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
