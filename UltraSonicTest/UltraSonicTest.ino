int echoPin = 2; 
int trigPin = 3; 
 
void setup() { 
  Serial.begin (115200); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.print("SETUP OF Nano for Ultrasonic Distance Sensor ");
} 
 
void loop() { 
  int duration, cm; 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  cm = duration / 58;
  // if distance is less than 10 cm turn on led ... builtin led or digital pin .. 
  
  Serial.print(cm); 
  Serial.println(" cm"); 
  delay(50);
}
