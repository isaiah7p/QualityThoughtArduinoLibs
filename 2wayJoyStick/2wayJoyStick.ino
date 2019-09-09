#include <Servo.h>

Servo myservoX; 
Servo myservoY;// create servo object to control a servo
// twelve servo objects can be created on most boards

int posX = 0;    // variable to store the servo position
int posY = 0;
const int ledPin =  13;
int analogPin = A0;     // potentiometer wiper (middle terminal) connected to analog pin 3
int analogPin1 = A10;                        // outside leads to ground and +5V
int sw = 2;
int xVal = 0;           // variable to store the value read
int yVal = 0;
 int buttonState = 0;
void setup()
{
  Serial.begin(9600);              //  setup serial
  pinMode(sw,INPUT);
    pinMode(ledPin, OUTPUT);
   myservoX.attach(9); 
    myservoY.attach(10); 
}

void loop()
{ 
  buttonState = digitalRead(sw);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  
  xVal = analogRead(analogPin);     // read the input pin
   yVal = analogRead(analogPin1);     // read the input 
  Serial.println("X & Y Raw  Values");   
  Serial.println(xVal);             // debug value
  Serial.println(yVal);             // debug value
  delay(100);
  //
posX = map(xVal,0,1023,0,180);
posY = map(yVal,0,1023,0,180);
 Serial.println("X & Y Position  Values");  
  Serial.println(posX);             // debug value
  Serial.println(posY);             // debug value

      myservoX.write(posX);              // tell servo to go to position in variable 'pos'
    delay(15);   
        myservoY.write(posY);              // tell servo to go to position in variable 'pos'
    delay(15);                 
}
