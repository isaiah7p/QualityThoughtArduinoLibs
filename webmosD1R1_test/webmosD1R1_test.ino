  // This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
  // Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 
  
  //#define CAYENNE_DEBUG
  #define CAYENNE_PRINT Serial
  #include <CayenneMQTTESP8266.h>
  #include <SimpleTimer.h>

  // WiFi network info.
  char ssid[] = "joelgloria";
  char wifiPassword[] = "b4b3c69b5267!";
  SimpleTimer timer;
  
  // for HC-SR04
  #define echoPin D4 // Echo Pin
  #define trigPin D5 // Trigger Pin
  
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, distance, distance_new, logecho; // Duration used to calculate distance
  
  
  // Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
  char username[] = "6fff5240-f05c-11e6-a971-4db18559717d";
  char password[] = "4a5495303e20c8e904dab1862802bb32990cd994";
  char clientID[] = "54dfae90-fef8-11e8-8e60-53d8c8eabc71";
  
  unsigned long lastMillis = 0;
  
  void setup() {
  	Serial.begin(9600);
  	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
   // timer.setInterval(60000, RepeatTask);
    timer.setInterval(6000, RepeatEcho);
  }
  CAYENNE_OUT(V3) {
    Cayenne.virtualWrite(V3,logecho); // virtualpin 3 plus distance
  }
  
  CAYENNE_OUT(V4) {
    Cayenne.virtualWrite(V4,distance); // virtualpin 4 plus distance
  }
  
  
  void loop() {
  	Cayenne.loop();
  // Cayenne.run(); // Initiates Blynk
     timer.run();   // Initiates SimpleTimer
  	//Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
  	if (millis() - lastMillis > 10000) {
  		lastMillis = millis();
  		//Write data to Cayenne here. This example just sends the current uptime in milliseconds.
  		Cayenne.virtualWrite(0, lastMillis);
  		//Some examples of other functions you can use to send data.
  		//Cayenne.celsiusWrite(1, 22.0);
  		//Cayenne.luxWrite(2, 700);
  		//Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
  	}
  
   
  
  }
  void RepeatEcho() {
  
  // Start of Section: HC-SR04 - Distance
    /* 
    The following trigPin/echoPin cycle is used to determine the
    distance of the nearest object by bouncing soundwaves off of it.
    The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    Give a short LOW pulse beforehand to ensure a clean HIGH pulse.
    */
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    duration = pulseIn(echoPin, HIGH);
    // Calculate the distance (in cm) based on the speed of sound.
    distance_new = duration/58.2 + (196 - 55); //including correctie of measure height: 196 cm height cellar, 55 cm height tube) 
    Serial.println(distance_new);
    if (145 <= distance_new <= 300 && distance_new < distance) { 
      distance = distance_new;                                                  
      }
  
  }
  
  //Default function for processing actuator commands from the Cayenne Dashboard.
  //You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
  //CAYENNE_IN_DEFAULT()
  //{
  //	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
  //}
