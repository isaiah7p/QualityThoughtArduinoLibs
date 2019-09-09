// Hardware: Arduino Duemilanove w/ ATmega328 and an Adafruit RGB 16x2 LCD Shield
// Project: Hackaday Logo made with 6 custom characters
// Compiled with: Arduino IDE 1.0.5

#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

byte icons[6][8] = { { 0x06,0x02,0x12,0x1e,0x01,0x02,0x02,0x02 },
                     { 0x00,0x00,0x00,0x1f,0x00,0x1b,0x11,0x00 },
                     { 0x0c,0x08,0x09,0x0f,0x10,0x08,0x08,0x08 },
                     { 0x01,0x01,0x1e,0x12,0x02,0x06,0x00,0x00 },
                     { 0x04,0x00,0x1f,0x15,0x00,0x00,0x00,0x00 },
                     { 0x10,0x10,0x0f,0x09,0x08,0x0c,0x00,0x00 } };
                     
/* A few other versions of the bottom center icon
0x04,0x00,0x1f,0x0a,0x00,0x00,0x00,0x00  // two "teeth"
0x04,0x00,0x11,0x0e,0x00,0x00,0x00,0x00  // "smile"
0x04,0x00,0x1f,0x0e,0x00,0x00,0x00,0x00  // "chin"
*/

const int top_left = 0;
const int top_center = 1;
const int top_right = 2;
const int bot_left = 3;
const int bot_center = 4;
const int bot_right = 5;

void setup()
{
  // set up number of columns and rows
  lcd.begin(16, 2);
  
  
    // Define custom icons
  lcd.createChar(top_left, icons[top_left]);
  lcd.createChar(top_center, icons[top_center]);
  lcd.createChar(top_right, icons[top_right]);
  lcd.createChar(bot_left, icons[bot_left]);
  lcd.createChar(bot_center, icons[bot_center]);
  lcd.createChar(bot_right, icons[bot_right]);


  // print the custom chars to the lcd
  lcd.write(top_left);
  lcd.write(top_center);
  lcd.write(top_right);
  
  lcd.print("  Hello   ");
  
  // print the custom chars to the lcd
  lcd.write(top_left);
  lcd.write(top_center);
  lcd.write(top_right);
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  
  // print the custom chars to the lcd
  lcd.write(bot_left);
  lcd.write(bot_center);
  lcd.write(bot_right);
  
  lcd.print(" Hackaday ");
  
  // print the custom chars to the lcd
  lcd.write(bot_left);
  lcd.write(bot_center);
  lcd.write(bot_right);
  
  lcd.setBacklight(WHITE);

}

void loop()
{ }
