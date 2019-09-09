 int ecg  = 0;

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(D1, INPUT); // Setup for leads off detection LO +
  pinMode(D2, INPUT); // Setup for leads off detection LO -

}

void loop() {
 
  if((digitalRead(D1) == 1)||(digitalRead(D2) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0:
      ecg = analogRead(A0);
      Serial.println(ecg);
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);
}
