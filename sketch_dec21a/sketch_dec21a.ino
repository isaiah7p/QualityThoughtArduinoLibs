int redledpin=8;
int yellowledpin=9;
int redledon=230;
int redledoff=230;
int yellowledon=230;
int yellowledoff=230;
void setup() {
pinMode(redledpin,OUTPUT);
pinMode(yellowledpin,OUTPUT);
} 
void loop() { // loop started 
  
for(int j=1;j<=5;j++){ // for loop started 
digitalWrite(redledpin,HIGH);
delay(redledon);
digitalWrite(redledpin,LOW);
delay(redledoff);

}// for loop closed 

digitalWrite(yellowledpin,HIGH);
delay(yellowledon);
digitalWrite(yellowledpin,LOW);
delay(yellowledoff);

} // loop closed 
