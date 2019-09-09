 int bytesSent = 0;
 String s1= "Hello";
void setup(){
  Serial.begin(9600);
}

void loop(){
 
  Serial.write(45); // send a byte with the value 45

   bytesSent = Serial.write(s1);
   Serial.println(bytesSent);
}

