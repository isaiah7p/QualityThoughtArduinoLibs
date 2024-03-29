#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 6); // STEP 1   // request 6 bytes from slave device #8

  while (Wire.available()) { // STEP 4 // slave may send less than requested
    char c = Wire.read(); // retriving I@C Values receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}
