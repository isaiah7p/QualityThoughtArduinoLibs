#include <Wire.h>

void setup() {
 Serial.begin(9600); 
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
           /* start serial for debug */
}
int i=0;
void loop() {
 delay(100);
 i++;
 Wire.write(i);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
// Wire.write("Hello NodeMCU");  /*send string on request */
  Serial.print(i); 
 Wire.write(i);
  Wire.write(i+10);
   Wire.write(i+20);
}
