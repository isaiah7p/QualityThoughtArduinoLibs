int i = 0;
int j = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println(" SETUP Method  ");
}

void loop() {
  // put your main code here, to run repeatedly:

  for( i = 0; i<255 ;i++){
    Serial.println(i);
    
    }
    for( j = 255; j>0 ;j--){
    Serial.println(j);
    
    }

}
