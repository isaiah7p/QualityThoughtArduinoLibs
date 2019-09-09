
int gpsVCCpin = 10;
int gpsGNDpin = 11;
void setup() {
  // put your setup code here, to run once:
pinMode(gpsVCCpin,OUTPUT);
pinMode(gpsGNDpin,OUTPUT);

// Switchig off LED 
digitalWrite(gpsVCCpin,LOW);

digitalWrite(gpsGNDpin,LOW);

delay(1000);
}
void loop() {
  // put your main code here, to run repeatedly:

  // LED ON 
digitalWrite(gpsVCCpin,HIGH);
digitalWrite(gpsGNDpin,LOW);
delay(1000);
  // LED OFF
digitalWrite(gpsVCCpin,LOW);
digitalWrite(gpsGNDpin,LOW);
delay(1000);
  
}
