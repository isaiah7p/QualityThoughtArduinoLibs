/*
  
 Created by Rui Santos
 
 All the resources for this project:
 https://randomnerdtutorials.com/
 
*/

int ledOpen=2;
int ledClose=4;
int switchReed=5;

void setup(){
  pinMode(ledOpen, OUTPUT);
  pinMode(ledClose, OUTPUT);
  pinMode(switchReed, INPUT);
  Serial.begin(9600);
}

void loop(){
  
  if (digitalRead(switchReed)==HIGH){
    digitalWrite(ledOpen, LOW);
    digitalWrite(ledClose, HIGH);
    Serial.println("Your Door is Closed");
  }
  else {
    digitalWrite(ledOpen, HIGH);
    digitalWrite(ledClose, LOW);
    Serial.println("Your Door is Open");
  }
  delay(1);
}
