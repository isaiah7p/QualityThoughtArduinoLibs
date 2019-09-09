int redledpin=8;
int yellowledpin=9;
int redledon=115;
int redledoff=115;
int yellowledon=115;
int yellowledoff=115;

void setup() {
pinMode(redledpin,OUTPUT);
pinMode(yellowledpin,OUTPUT);
} 

void loop() { // loop started 
for(int j=1;j<=10;j++){ // for loop started 
digitalWrite(redledpin,HIGH);
delay(redledon);
digitalWrite(redledpin,LOW);
delay(redledoff);
}
for(int i=1;i<=5;i++){ // for loop started
digitalWrite(yellowledpin,HIGH);
delay(yellowledon);
digitalWrite(yellowledpin,LOW);
delay(yellowledoff);
}
}// for loop closed

