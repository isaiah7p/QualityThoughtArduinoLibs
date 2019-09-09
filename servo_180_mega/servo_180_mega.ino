#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo1.attach(10);
}

void loop() {
 // val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
 // val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)

 for(int i=0 ; i<180 ;i=i+30){
  myservo.write(i);                  // sets the servo position according to the scaled value
  delay(200);     
 }// waits for the servo to get there
 // Delay 
 
 delay(1000);
  
  for(int j=180; j>0 ;j=j-30){
  myservo.write(j);                  // sets the servo position according to the scaled value
  delay(200);     
 }
 for(int k=0 ; k<180 ;k=k+30){
  myservo1.write(k);                  // sets the servo position according to the scaled value
  delay(200);     
 }// waits for the servo to get there
 // Delay 
 
 delay(1000);
  
  for(int l=180; l>0 ;l=l-30){
  myservo1.write(l);                  // sets the servo position according to the scaled value
  delay(200);     
 }
}


