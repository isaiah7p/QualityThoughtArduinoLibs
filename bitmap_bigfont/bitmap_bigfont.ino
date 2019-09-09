
// These constants won't change. They're used to give names 
// to the pins used: 
const int analogInPin = A0; // Analog input pin that the potentiometer is attached to 

int sensorValue = 0; // value read from the pot 
int outputValue = 0; // value output to the PWM (analog out) 
//char outputValueChar[5]; 
int hundreds; 
int tens; 
int ones; 
 #include <LiquidCrystal.h>
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 


// the 8 arrays that form each segment of the custom numbers 
byte LT[8] = 
{ 
B00111, 
B01111, 
B11111, 
B11111, 
B11111, 
B11111, 
B11111, 
B11111 
}; 
byte UB[8] = 
{ 
B11111, 
B11111, 
B11111, 
B00000, 
B00000, 
B00000, 
B00000, 
B00000 
}; 
byte RT[8] = 
{ 
B11100, 
B11110, 
B11111, 
B11111, 
B11111, 
B11111, 
B11111, 
B11111 
}; 
byte LL[8] = 
{ 
B11111, 
B11111, 
B11111, 
B11111, 
B11111, 
B11111, 
B01111, 
B00111 
}; 
byte LB[8] = 
{ 
B00000, 
B00000, 
B00000, 
B00000, 
B00000, 
B11111, 
B11111, 
B11111 
}; 
byte LR[8] = 
{ 
B11111, 
B11111, 
B11111, 
B11111, 
B11111, 
B11111, 
B11110, 
B11100 
}; 
byte UMB[8] = 
{ 
B11111, 
B11111, 
B11111, 
B00000, 
B00000, 
B00000, 
B11111, 
B11111 
}; 
byte LMB[8] = 
{ 
B11111, 
B00000, 
B00000, 
B00000, 
B00000, 
B11111, 
B11111, 
B11111 
}; 

// loop counter 
int x = 0; 


void setup() 
{ 
Serial.begin(9600); 
// assignes each segment a write number 
lcd.createChar(0,LT); 
lcd.createChar(1,UB); 
lcd.createChar(2,RT); 
lcd.createChar(3,LL); 
lcd.createChar(4,LB); 
lcd.createChar(5,LR); 
lcd.createChar(6,UMB); 
lcd.createChar(7,LMB); 


// sets the LCD's rows and colums: 
lcd.begin(16, 2); 

} 

void custom0() 
{ // uses segments to build the number 0 
lcd.setCursor(x, 0); // set cursor to column 0, line 0 (first row) 
lcd.write((byte)0); // call each segment to create 
lcd.write(1); // top half of the number 
lcd.write(2); 
lcd.setCursor(x, 1); // set cursor to colum 0, line 1 (second row) 
lcd.write(3); // call each segment to create 
lcd.write(4); // bottom half of the number 
lcd.write(5); 
} 

void custom1() 
{ 
lcd.setCursor(x,0); 
lcd.write(1); 
lcd.write(2); 
lcd.setCursor(x+1,1); 
lcd.write(5); 
} 

void custom2() 
{ 
lcd.setCursor(x,0); 
lcd.write(6); 
lcd.write(6); 
lcd.write(2); 
lcd.setCursor(x, 1); 
lcd.write(3); 
lcd.write(7); 
lcd.write(7); 
} 

void custom3() 
{ 
lcd.setCursor(x,0); 
lcd.write(6); 
lcd.write(6); 
lcd.write(2); 
lcd.setCursor(x, 1); 
lcd.write(7); 
lcd.write(7); 
lcd.write(5); 
} 

void custom4() 
{ 
lcd.setCursor(x,0); 
lcd.write(3); 
lcd.write(4); 
lcd.write(2); 
lcd.setCursor(x+2, 1); 
lcd.write(5); 
} 

void custom5() 
{ 
lcd.setCursor(x,0); 
lcd.write((byte)0); 
lcd.write(6); 
lcd.write(6); 
lcd.setCursor(x, 1); 
lcd.write(7); 
lcd.write(7); 
lcd.write(5); 
} 

void custom6() 
{ 
lcd.setCursor(x,0); 
lcd.write((byte)0); 
lcd.write(6); 
lcd.write(6); 
lcd.setCursor(x, 1); 
lcd.write(3); 
lcd.write(7); 
lcd.write(5); 
} 

void custom7() 
{ 
lcd.setCursor(x,0); 
lcd.write(1); 
lcd.write(1); 
lcd.write(2); 
lcd.setCursor(x+1, 1); 
lcd.write((byte)0); 
} 

void custom8() 
{ 
lcd.setCursor(x,0); 
lcd.write((byte)0); 
lcd.write(6); 
lcd.write(2); 
lcd.setCursor(x, 1); 
lcd.write(3); 
lcd.write(7); 
lcd.write(5); 
} 

void custom9() 
{ 
lcd.setCursor(x,0); 
lcd.write((byte)0); 
lcd.write(6); 
lcd.write(2); 
lcd.setCursor(x+2, 1); 
lcd.write(5); 
} 





void loop() { 
// read the analog in value: 
sensorValue = analogRead(analogInPin); 
// map it to the range of the analog out: 
outputValue = map(sensorValue, 0, 1023, 0, 360); 

// print the results to the serial monitor: 
Serial.print("sensor = " ); 
Serial.print(sensorValue); 
Serial.print("\t output = "); 
Serial.println(outputValue); 

String stringOne = String(outputValue); 
// prints the value of outputValue 
//Serial.print("Output value string is "); 
//Serial.println(stringOne); 
x=0; 
hundreds = outputValue /100; 
//Serial.print(hundreds); 
delay(500); 

switch (hundreds) { 
case 3: 
custom3(); 
break; 

case 2: 

custom2(); 
break; 

case 1: 

custom1(); 
break; 

case 0: 

custom0(); 
break; 

} 

tens=outputValue /10; 
tens=tens%10; 
//Serial.println(tens); 

switch (tens) { 
case 9: 
x=x+3; 

custom9(); 
break; 

case 8: 
x=x+3; 

custom8(); 
break; 

case 7: 
x=x+2; 

custom7(); 
break; 

case 6: 
x=x+3; 

custom6(); 
break; 

case 5: 
x=x+3; 

custom5(); 
break; 

case 4: 
x=x+3; 

custom4(); 
break; 

case 3: 
x=x+3; 

custom3(); 
break; 

case 2: 
x=x+3; 

custom2(); 
break; 

case 1: 
x=x+3; 

custom1(); 
break; 

if (outputValue<10) 
{ 
//case 0: 
x=x+3; 

custom0(); 
break; 
} 

case 0: 
x=x+3; 

custom0(); 
break; 
} 

ones=outputValue%10; 
//ones=ones%100; 
// Serial.println(ones); 

switch (ones) { 
case 9: 
x=x+3; 

custom9(); 
break; 

case 8: 
x=x+3; 

custom8(); 
break; 

case 7: 
x=x+3; 

custom7(); 
break; 

case 6: 
x=x+3; 

custom6(); 
break; 

case 5: 
x=x+3; 

custom5(); 
break; 

case 4: 
x=x+3; 

custom4(); 
break; 

case 3: 
x=x+3; 

custom3(); 
break; 

case 2: 
x=x+3; 

custom2(); 
break; 

case 1: 
x=x+3; 

custom1(); 
break; 

case 0: 
x=x+3; 

custom0(); 
break; 

} 
/* 
delay(500); 
lcd.setCursor(0,1); 
lcd.print(outputValue); */ 
//delay(300); 
//lcd.clear(); 

//if (outputValue < 100) 
// { 
// x=0; 
// lcd.print(" "); 
// } 

// wait 2 milliseconds before the next loop 
// for the analog-to-digital converter to settle 
// after the last reading: 
//delay(10); 


}
