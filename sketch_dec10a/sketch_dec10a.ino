float heartRate = 0;
int hrPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  heartRate =  analogRead(A0);
  if (!isnan(heartRate)) {
    Serial.println("Heart Rate ::");
    Serial.print(heartRate);
  } else {
    Serial.println("Error Reading the sensor Data !! ");

  }


}
