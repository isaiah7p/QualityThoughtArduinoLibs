int i =0;
int j = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  Serial.println("  in setup method ");
  
}

void loop() {
  i = i+2123 ;
  j = j+1222 ;
  // put your main code here, to run repeatedly:
 Serial.println("  in loop  method ");
 Serial.println(i);
 Serial.println(j);
 delay(500);
}
