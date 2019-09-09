#include <Servo.h>


Servo myservo;  // create servo object to control a servo
Servo myservo1;
//int count= 0; 
// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A1; // analog pin connected to X output
const int Y_pin = A2; // analog pin connected to Y output

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo1.attach(10); 
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  int xVal,yVal;
  xVal = analogRead(X_pin);  // xVal = 1023  0 - 180 ... 
  Serial.print(xVal);
  int xAngle ,yAngle ; 
  xAngle =  map(xVal,0,1023,0,180);
  myservo.write(xAngle);
  yVal= analogRead(Y_pin);   // yVal 0 - 1023 
  yAngle =  map(yVal,0,1023,0,180);
  myservo1.write(yAngle); 
  Serial.print(xVal);   // sets the servo position according to the scaled value

}


