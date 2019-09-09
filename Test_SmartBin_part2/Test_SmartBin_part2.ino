#include <Servo.h>

int objectDetectionPin = 2;
int sensoroutput = 4; // the analog pin connected to the sensor

int THRESHOLD = 100;

Servo servo1;
Servo servo2;
int val = 0; 
int  dryorwetConditionPin = 8;
int inVal =0;
void setup()
{
  Serial.begin (9600);
  //  pinMode(trigPin, OUTPUT);
  //  pinMode(echoPin, INPUT);
  pinMode(dryorwetConditionPin, INPUT);
  pinMode(objectDetectionPin, INPUT);

  servo1.attach(4);
  servo2.attach(5);
  Serial.println(" === Setup Method   ===");
  servo1.write(90);
  servo2.write(90);
  Serial.println(" === Initial Position Method   ===");
  // delay(5000);

}

void loop() {
    
  int val = analogRead(sensoroutput);
  Serial.print(val);
  if (val >= THRESHOLD) {

    Serial.print(" ====  Object found ======== ");

      inVal= digitalRead(dryorwetConditionPin);
    Serial.print(">>>> Value:::");
    Serial.println(inVal);

   

      servo1.write(0);
      servo2.write(180);
      delay(5000);
  

  }else{
     val = 0;
      Serial.println(" ===No Object Found    ===");
    }
    // resetting condition 
    
   servo1.write(90);
   servo2.write(90);
  delay(2000);
}
