

int analogXPin = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3
int analogYPin = 4;
int analogZPin = 5;// outside leads to ground and +5V
int valX = 0;           // variable to store the value read
int valY = 0;
int valZ = 0;
void setup()
{
  Serial.begin(9600);              //  setup serial
}

void loop()
{
  valX = analogRead(analogXPin);     // read the input pin
  valY = analogRead(analogYPin);     // read the input pin
  valZ = analogRead(analogZPin);     // read the input pin
  Serial.println(valX);             // debug value
   Serial.println(valY);
    Serial.println(valZ);
    delay(1000);
}
