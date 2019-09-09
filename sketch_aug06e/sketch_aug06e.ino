
int ledPin = 52;
int count = 0;
int loopCount = 0;
void setup()
{
  pinMode(ledPin, OUTPUT);          // sets the digital pin 13 as output
  Serial.begin(9600);
  Serial.println(loopCount);
    // Add code to here
    pinMode(11,INPUT);
    pinMode(12,INPUT);
    pinMode(13,INPUT);
}

void loop()
{ 
  for(count;count<5;count++){
  
  digitalWrite(ledPin, HIGH);       // sets the digital pin 13 on
  delay(1000);                  // waits for a second
  digitalWrite(ledPin, LOW);        // sets the digital pin 13 off
  delay(1000);                  // waits for a second
  
  }
   Serial.println(loopCount);
  loopCount++;
  delay(1000);
}

