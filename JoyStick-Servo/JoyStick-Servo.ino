
#include <Servo.h>

Servo myservoX;
Servo myservoY;
int valX=0;
int valY=0;

void setup() {
  // put your setup code here, to run once:
myservoX.attach(9);
myservoY.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
valX = analogRead(A0); // 0 -1023 
valY = analogRead(A1); // 0- 1023 
// Mapping 
valX = map(valX,0,1023,0,180);
valY = map(valY,0,1023,0,180);

myservoX.write(valX);   // 0 -  180  
myservoY.write(valY);   // 0- 180 
}
