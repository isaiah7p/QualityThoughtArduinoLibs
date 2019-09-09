#include<Servo.h>
// joystick readings 
#define x A0
#define y A1
// servo pins 
#define s1 9
#define s2 10 
// temp varaiables 
int xVal, yVal ; 
// servos declarations 
Servo xServo;
Servo yServo;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
// attach servos to defined pins .... 
xServo.attach(s1);
yServo.attach(s2);
Serial.println("Begining the serial ......");
}

void loop() {
  // put your main code here, to run repeatedly:


 /// Capturing input data 
 xVal = analogRead(x);  // 0 1024 
 
 yVal = analogRead(y);  // 0 1024 
    
Serial.println("x >> ");
Serial.println(xVal);
Serial.println(" y >> ");
Serial.println(yVal);

// convert input data to rotational angle 
 xVal=map(xVal,0,1024,0,180);
 yVal=map(yVal,0,1024,0,180);

Serial.println("x Roation >> ");
Serial.println(xVal);
Serial.println(" y Rotation  >> ");
Serial.println(yVal);

// rotating motors or servos 

xServo.write(xVal);
yServo.write(yVal);


}
