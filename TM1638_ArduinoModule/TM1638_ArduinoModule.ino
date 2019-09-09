const int strobe = 7;
const int clock = 9;
const int data = 8;
 
 
 
void sendCommand(uint8_t value)
{
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, value);
  digitalWrite(strobe, HIGH);
}
 
void reset()
{
  sendCommand(0x40); // set auto increment mode
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xc0);   // set starting address to 0
  for(uint8_t i = 0; i < 16; i++)
  {
    shiftOut(data, clock, LSBFIRST, 0x00);
  }
  digitalWrite(strobe, HIGH);
}
 
void setup()
{
  pinMode(strobe, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
 
  sendCommand(0x8f);  // activate
  reset();
  sendCommand(0x44);  // set single address
}
 
void loop()
{
 
 
 for (int i=0;i<16;)
 {
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xc1+i); // led on
  shiftOut(data, clock, LSBFIRST, 1);
  digitalWrite(strobe, HIGH);
  delay(100);
   digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xc1+i); // led off
  shiftOut(data, clock, LSBFIRST,0);
  digitalWrite(strobe, HIGH);
   delay(10);
   i+=2;
 }
 
 
 
 
 
}
