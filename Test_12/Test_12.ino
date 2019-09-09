

void setup()
{
  pinMode(D2, OUTPUT);          // sets the digital pin 13 as output
}

void loop()
{
  digitalWrite(D2, HIGH);       // sets the digital pin 13 on
  delay(100);                  // waits for a second
  digitalWrite(D2, LOW);        // sets the digital pin 13 off
  delay(100);                  // waits for a second
}

