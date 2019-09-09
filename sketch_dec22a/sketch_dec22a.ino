int RECV_PIN=11;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup ()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinmode(12,OUTPUT);
}
void Loop () {
  
  if (irrecv.decode(results)){
  Serial.printIn(results.value,DEC);
  if (results.value==17024855)
  }
Serial.printIN("Button Pressed");
if (digitalRead(12)==LOW)
digitalWrite(12,HIGH);

else
  digitalWrite(12,LOW);

}
