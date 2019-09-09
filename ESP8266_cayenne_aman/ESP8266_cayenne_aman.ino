#include <Wire.h>

void setup() {
 Serial.begin(9600); /* begin serial for debug */
 Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
}

void loop() {
 Wire.beginTransmission(8); /* begin with device address 8 */
 Wire.write("Hello Arduino");  /* sends hello string */
 Wire.endTransmission();    /* stop transmitting */

 Wire.requestFrom(8, 37); /* request & read data of size 13 from slave */
 while(Wire.available()){
    char c = Wire.read();
  Serial.print(c);
 }
 //Serial.println(" ");
 char c1 = Wire.read();
  Serial.print(c1);
 //Serial.println();
 // Serial.println(" ");
 char c2 = Wire.read();
  Serial.print(c2);
 //Serial.println();
 // Serial.println(" ");
 char c3 = Wire.read();
  Serial.print(c3);
 //Serial.println();
//  Serial.println(" ");
 char c4 = Wire.read();
  Serial.print(c4);
 //Serial.println();
//  Serial.println(" ");
 char c5 = Wire.read();
  Serial.print(c5);
// Serial.println();
  //Serial.println(" ");
 char c6 = Wire.read();
  Serial.print(c6);
 
 delay(1000);
}
