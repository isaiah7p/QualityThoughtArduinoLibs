void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  int val = digitalRead(11);
  Serial.print("Input Val : ");
  Serial.println(val);
  digitalWrite(13,HIGH);
    Serial.print("LED ON ");
  delay(100);
  digitalWrite(13,LOW);
   Serial.print("LED OFF ");
  delay(100);
  digitalWrite(12,val);
 Serial.print("BUTTON VALUE");
  delay(100);
  
}
