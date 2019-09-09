
int x = A0; 
int y = A1; 
int z = A2; 


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Testing xyz sensor ");
}

void loop() {
  // put your main code here, to run repeatedly:

int xVal = analogRead(x);
int yVal = analogRead(y);
int zVal = analogRead(z);
Serial.println("x:  ");
Serial.println(xVal);
Serial.println("y:  ");
Serial.println(yVal);
Serial.println("z:  ");
Serial.println(zVal);

delay(1000);

}
