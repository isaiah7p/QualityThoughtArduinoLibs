
int pinLed = 13 ; 
void setup() {
  // put your setup code here, to run once:
  pinMode(pinLed,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:  

  digitalWrite(pinLed,HIGH);
  delay(2000); // 2000 milli seconds - 2 secs
   digitalWrite(pinLed,LOW);
  delay(2000);

}
