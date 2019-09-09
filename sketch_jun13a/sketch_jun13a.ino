int ecgPin=A10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  float ecgVal = analogRead(ecgPin);
  Serial.print("Ecg : ");
   Serial.println(ecgVal);
  

}
