#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define I2C_ADDR 0x3F // <<- Add your address here.
#define Rs_pin 0
#define Rw_pin 1
#define En_pin 2
#define BACKLIGHT_PIN 3
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

#define ECHO_PIN 11 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN 12 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

bool backLightOn = true;


// NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
 Serial.begin(9600);
 lcd.begin (16,2); // <<-- our LCD is a 20x4, change for your LCD if needed
 lcd.clear();
// LCD Backlight ON
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);

lcd.home (); // go home on LCD
lcd.print("Range Finder HC-SR04"); 
Serial.print(" done SetUp for  HC-SR04");
}

void loop()
{
  
 // Serial.print(" loop HC-SR04");
// unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
// unsigned int cm = sonar.convert_cm(uS); // Convert into centimeters

// Serial.println(sonar.ping());

 //Serial.println(sonar.convert_cm(uS));
if(backLightOn){
  
  lcd.setBacklight(HIGH);
     backLightOn = false;

       lcd.clear();
 lcd.setCursor (0,0); // go to start of 1nd line
 lcd.print("Current Distance:");
 lcd.setCursor (0,1); // go to start of 2th line
 lcd.print("Ping: ");
//lcd.print(cm);
 lcd.print(" cm ");
 
  }else {

    lcd.setBacklight(LOW);
    backLightOn = true;

      lcd.clear();
 lcd.setCursor (0,0); // go to start of 1nd line
 lcd.print("Current Distance:");
 lcd.setCursor (0,1); // go to start of 2th line
 lcd.print("Ping: ");
//lcd.print(cm);
 lcd.print(" cm ");
    }


 delay(500);
}
