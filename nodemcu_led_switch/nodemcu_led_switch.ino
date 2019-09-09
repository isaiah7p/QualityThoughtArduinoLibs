// Include Libraries
#include "Arduino.h"


// Pin Definitions
#define LEDR_PIN_VIN  4
#define PUSHBUTTON_PIN_2  5



// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
     pinMode(LEDR_PIN_VIN,OUTPUT);
     pinMode(PUSHBUTTON_PIN_2,INPUT);
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
int val  =  digitalRead(PUSHBUTTON_PIN_2);

  Serial.println(val);
  if(val==1){
    digitalWrite(LEDR_PIN_VIN,HIGH);
     delay(2000);
    }
    digitalWrite(LEDR_PIN_VIN,LOW);
    delay(1000);
    
    // You have chosen a controller that doesn't have code yet.
    // You may request a similar combination but with Arduino Uno and try to use the Arduino Uno libraries & code - some may work, but we can't guarantee it. 
    // Make sure your Arduino IDE supports the chosen controller. If not visit http://playground.arduino.cc/Main/BoardsManagerSupport
    
}

