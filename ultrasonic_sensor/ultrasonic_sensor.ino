int echoPin = 2; 
int trigPin =3;



void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(echoPin,INPUT);
pinMode(trigPin,OUTPUT);

Serial.print(" started sensor");
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int duration , cm ; 

  // pulse generation 
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(2);         L

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  
  // waiting for the pulse duration 
  
  duration=pulseIn(echoPin,HIGH);

  // distance calculation 

  cm = duration/58; 

  Serial.print("cm");
Serial.println(cm);
}
