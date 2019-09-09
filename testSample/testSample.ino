void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(" This is from SetUp Method  ");
  delay(1000);

  // for Initialisations 
  // Check any of the sensors status 
  // start any comminications like wifi bluetooth ,Radion Frequency comms , Lora , ethernet . GSM or GPRS 
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(" This is from loop Method  ");
  delay(1000);
  // repeatition tasks 
  // get sensor data 
  // upload to the server 
  
}
