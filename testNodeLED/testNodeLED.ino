int led = 4; 

void setup() {
  // put your setup code here, to run once:
 pinMode(led,OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//digitalWrite(led,HIGH);
Serial.println("LED IS HIGH ");
delay(1000);
//digitalWrite(led,LOW);
Serial.println("LED IS LOW ");
delay(1000);
}
