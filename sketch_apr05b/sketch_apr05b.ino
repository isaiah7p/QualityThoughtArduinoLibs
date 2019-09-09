
// Include Libraries
#include "Arduino.h"

// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    Serial.println(F(" Type Your Name "));
   
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
 //Serial.println(F(" Type Your Name "));
    while (!Serial.available());
    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        Serial.print(c);
    
    }
    Serial.flush();
    //delay(2000);
}
