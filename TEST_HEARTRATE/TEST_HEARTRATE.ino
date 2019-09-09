
int UpperThreshold = 518;
int LowerThreshold = 490;
    int reading = 0;
    float BPM = 0.0;
    bool IgnoreReading = false;
    bool FirstPulseDetected = false;
    unsigned long FirstPulseTime = 0;
    unsigned long SecondPulseTime = 0;
    unsigned long PulseInterval = 0;



void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  Serial.println("Hr : ");
  // put your main code here, to run repeatedly:

    reading = analogRead(A0); 
      if(reading > UpperThreshold && IgnoreReading == false){
        if(FirstPulseDetected == false){
          FirstPulseTime = millis();
          FirstPulseDetected = true;
        }
        else{
          SecondPulseTime = millis();
          PulseInterval = SecondPulseTime - FirstPulseTime;
          FirstPulseTime = SecondPulseTime;
        }
        IgnoreReading = true;
      }
      if(reading < LowerThreshold){
        IgnoreReading = false;
      }  

      BPM = (1.0/PulseInterval) * 60.0 * 1000;
      Serial.println(BPM);
delay(1000);
}
