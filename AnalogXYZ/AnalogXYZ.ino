void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//Serial.println("in Loop Method ");

int aX = analogRead(A0);

int aY = analogRead(A1);

int aZ = analogRead(A2);

float callI = functionA(aX);

Serial.println(aX);
Serial.println(aY);
Serial.println(aZ);
}
