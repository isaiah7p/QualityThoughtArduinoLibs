/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

void setup()
{
   pinMode(5, OUTPUT);
   pinMode(4, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
   digitalWrite(5, HIGH);
   digitalWrite(4, HIGH);
   delay(1000); // Wait for 1000 millisecond(s)
  // turn the LED off by making the voltage LOW
   digitalWrite(5, LOW);
 // delay(400); // Wait for 1000 millisecond(s)
 
 // delay(400); // Wait for 1000 millisecond(s)
  // turn the LED off by making the voltage LOW
   digitalWrite(4, LOW);
 // delay(400); // Wait for 1000 millisecond(s)
   delay(1000);
}
