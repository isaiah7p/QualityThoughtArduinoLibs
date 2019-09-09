#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;
byte y = 0;
void loop() {
  y=x+1231;
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.write("y is "); 
  Wire.write(y); 
  Wire.endTransmission();    // stop transmitting
  
  x++;
  delay(500);
}
