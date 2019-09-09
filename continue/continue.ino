int x;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (x = 0; x <= 255; x ++)
  {
    if (x > 40 && x < 120){      // create jump in values
        continue;
    }

    Serial.println(x);
    delay(50);
  }

}
