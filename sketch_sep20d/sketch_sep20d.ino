
#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // STEP 2  // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {  // STEP 3 Execution 
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
  //DHT sensor 
  // temp sensor 
  // Distance Sensor 
  // IR sensor 
}
