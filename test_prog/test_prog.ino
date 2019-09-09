void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(" IN SETUP Method ");

}

int counter =1 ;

void loop() {
  // put your main code here, to run repeatedly:
    
    Serial.println(" IN LOOP Method ");
      Serial.println(counter);
    
    counter++;
}
