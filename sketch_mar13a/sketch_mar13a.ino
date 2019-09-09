void setup(){
  Serial.begin(9600);
}
int r = 1;
void loop(){
  Serial.println("Hello World!");   
  delay(2000);
  if(Serial.available()){         //From RPi to Arduino
    r = r * (Serial.read() - '0');  //conveting the value of chars to integer
    Serial.println(r);
  }
  
}
