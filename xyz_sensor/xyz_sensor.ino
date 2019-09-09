// This is a simple working-example to quick measuring:
// 1. the x, y and z-values read from a GY-61-acceleration-module
// 2. an angle in eg. the x-direction

// You can put the module in 4 directions to determine the min-max-values:
// –>   0deg   x = 349  y = 341  z = 425
// /\    90deg  x = 281  y = 345  z = 357
// <–  180deg  x = 350  y = 345  z = 288
//  V   270deg  x = 419  y = 341  z = 355
// This can be used to measure degrees

// you can use all the analog inputs to control the GY-61
// picture: https://www.fabtolab.com/ADXL335-GY61?search=gy-61
//const int VCCPin = A0;
const int xPin   = A0;
const int yPin   = A1;
const int zPin   = A2;
//const int GNDPin = A4;

// variables
int x = 0;
int y = 0;
int z = 0;

void setup() {
// pin A0 (pin14) is VCC and pin A4 (pin18) in GND to activate the GY-61-module
//pinMode(A0, OUTPUT);
//pinMode(A4, OUTPUT);
//digitalWrite(14, HIGH);
//digitalWrite(18, LOW);

// activating debugging for arduino UNO
Serial.begin(9600);
} // end setup

void loop() {
x = analogRead(xPin);
y = analogRead(yPin);
z = analogRead(zPin);
// show x, y and z-values
Serial.print("x = ");
Serial.print(x);
Serial.print("  y = ");
Serial.print(y);
Serial.print("  z = ");
Serial.print(z);
// show angle"
Serial.print("angle = ");
Serial.println(constrain(map(x,349,281,0,90),0,90));
} // end loop


