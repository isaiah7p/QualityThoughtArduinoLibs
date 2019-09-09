#include <Servo.h>
Servo servo;
Servo servo1;
// Arduino Mega or Arduino Pins 
// 

int xPin = A2;
int yPin = A1;
int buttonPin = 2;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

void setup() {
  Serial.begin(9600);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  // servo connected pins 
  servo.attach(9);
  servo1.attach(10);
  // reset the servo positions 
 // servo.write(0);
  // servo1.write(0);
}

// 
void loop() {
  // read values from joy stick 
  
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(buttonState);
  // state of digital pin 
  digitalWrite(11, buttonState);
    // write values to serco 
  float yAngle = map(yPosition , 170,750,0,180);
  float xAngle = map(xPosition , 250,600,0,180);  
    Serial.print("X Angle: ");
  Serial.print(xAngle);
  Serial.print(" | Y Angle: ");
  Serial.print(yAngle);
    servo.write(xAngle);
    servo1.write(yAngle);

  delay(10);
}
