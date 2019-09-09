/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput
*/

int xPin = A10;    // select the input pin for the potentiometer
int yPin = A0;    // select the input pin for the potentiometer
int sw = 2;      // select the pin for the LED
int swValue = 0;  // variable to store the value coming from the sensor

int ifdl10 = 3;
int ifdg40 = 4; 

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(sw, INPUT);
    pinMode(ifdl10, INPUT);
       pinMode(ifdg40, INPUT);
  Serial.begin(9600);  
}
void loop() {
  // read the value from the sensor:
 int xVal =  analogRead(xPin);
 int yVal =  analogRead(yPin);
  Serial.println(xVal);
  Serial.println(yVal);

  // read from switch 
  swValue = digitalRead(sw); 
  
// sending value to builtin led 
  digitalWrite(LED_BUILTIN,swValue);

  Serial.println(swValue);
  
  delay(500);
}
