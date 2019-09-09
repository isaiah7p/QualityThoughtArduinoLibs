int xOut = A0;
int yOut = A1; 
int zOut = A2; 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Read values from analog sensor 
int xVal = analogRead(xOut);
int yVal = analogRead(yOut);
int zVal = analogRead(zOut);
  // write values to Serial Monitor 
Serial.println(xVal);
Serial.println(yVal);
Serial.println(zVal);
delay(200);
}
