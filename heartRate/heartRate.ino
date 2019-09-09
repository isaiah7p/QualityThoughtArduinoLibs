float heartrate = 0;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Heart Rate BPM ::: ");

  heartrate = analogRead(A0);

  if(heartrate!=0){

      Serial.println(heartrate);
  
    }
}
