void setup() 
{
  Serial.begin(2400);
  Serial.write("AT+CMGF=1\r"); // Set GSM to text mode
  delay(1500);

  Serial.write("+++");         // Test Command
  delay(1000);
  while(1)
  {
    if(Serial.available())
    {
      Serial.write(Serial.read());  
    }   
  }   
}

void loop() 
{

}
