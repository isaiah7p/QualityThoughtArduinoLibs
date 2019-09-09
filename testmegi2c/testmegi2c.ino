#include <Wire.h>

void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);           /* start serial for debug */
}

void loop() {
 delay(100);
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
 Wire.write("222342.50292923793376302052.9815.63");  /*send string on request */
// Wire.write("EHLAO");
// Wire.write("Pello");
// Wire.write("Eello");
// Wire.write("Mello");
// Wire.write("Jello");
// Wire.write("Iello");
// Wire.write("Kello");
// Wire.write("Sello");
// Wire.write("Qello");
 
}
