void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);


}

void loop(){
    Serial.print("Test"); 
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.print(inByte);
  }

  delay(100);
}
