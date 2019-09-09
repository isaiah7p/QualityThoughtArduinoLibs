#include <Wire.h>

void setup() {
 Serial.begin(9600); /* begin serial for debug */
 Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
}

void loop() {
 Wire.beginTransmission(8); /* begin with device address 8 */
 Wire.write("Hello Arduino");  /* sends hello string */
 Wire.endTransmission();    /* stop transmitting */

 Wire.requestFrom(8, 27); /* request & read data of size 13 from slave */
 while(Wire.available()){
    char c = Wire.read();
  Serial.print(c);
 }
 //Serial.println();
 char d = Wire.read();
  Serial.print(d);
 // Serial.println();
  char e = Wire.read();
  Serial.print(e);
 //while(Wire.available()){
    char f = Wire.read();
  Serial.print(f);
 //}
 //Serial.println();
 char g = Wire.read();
  Serial.print(g);
 // Serial.println();
  char h = Wire.read();
  Serial.print(h); 
 Serial.println();
 delay(1000);
}
