int x = A0;
int y = A1;
int z = A2;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println(" -- in setup method ---");
}

void loop() {

  //delay(2000);
  
  // put your main code here, to run repeatedly:

  float xVal = analogRead(x);
  
  float yVal = analogRead(y);

  float zVal = analogRead(z);

  Serial.print("x value : ");
  Serial.print(xVal);
  Serial.print(" y value : ");
    Serial.print(yVal);
  Serial.print(" z value : ");
    Serial.print(zVal);
    Serial.println("");


}
