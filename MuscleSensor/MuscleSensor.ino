void setup() {
  // initialize the serial communication:
  Serial.begin(9600);

}

void loop() {
    // send the value of analog input 0:
      Serial.println(analogRead(A0));

  delay(100);
}
