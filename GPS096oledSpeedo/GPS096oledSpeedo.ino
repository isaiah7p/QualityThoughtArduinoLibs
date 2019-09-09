#include <GPSfix_cfg.h>
#include <NeoGPS_cfg.h>
#include <NMEAGPS_cfg.h>

// #include <SPI.h>  // this sketch uses NeoSWSerial instead
// #include <Wire.h> // This  if for connecting I2C, again, not used.
// #include <Adafruit_GFX.h>//Adafruit Graphic Effects. Not used to, to save flash memory. GFX is a memory hog
#include <Adafruit_SSD1306.h>
#include <NeoSWSerial.h>

NeoSWSerial gps_port(4, 3);  //  assigns GPS to ports 4,3

#include "NMEAGPS.h"

static NMEAGPS  gps; // This parses the GPS characters

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


uint32_t timer;


void setup() {

  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars

  gps_port.begin(9600);

  // request RMC and GGA only
  gps_port.println( F("$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28") );

  display.begin(SSD1306_SWITCHCAPVCC);

  display.clearDisplay();// Clears the adafruit splash screen from flash memory
  display.setTextSize(2.5);
  display.setTextColor(WHITE);
  display.setCursor(15, 15);
  display.println( F("Mini-GPS"));
  display.setTextSize(1.8);
  display.setCursor(31, 40);
  display.print( F("Speedometer"));
  display.display(); // SEND SPLASH SCREEN
  delay(3000);       //  WAIT 3 SECONDS
  // timer = millis();
}


void loop()    // run over and over again
{


  while (gps_port.available()) {

    timer = millis(); // reset the timer

    if (gps.decode( gps_port.read() ) == NMEAGPS::DECODE_COMPLETED) {

      if (gps.nmeaMessage == NMEAGPS::NMEA_RMC) {
        //  If your device emits a GGA then an RMC each second,
        //    change the above GGA to RMC.  Or if you don't get all
        //    the attributes (e.g., alt, heading, speed and satellites)
        //    try changing the above test.  NMEAorder.ino can be
        //    used to determine which one is last (should be used above).

        //  BTW, this is the safest place to do any time-consuming work,
        //    like updating the display.  Doing it elsewhere will cause GPS
        //    characters to be lost, and some fix data won't be available/valid.
        //    And if you take too long here, you could still lose characters.

        uint32_t displayTime = micros(); // use this later, to figure out how long the display process takes.



        display.clearDisplay(); //CLEAR THE OLED BUFFER, THUS CLEARING THE SCREEN:  GOT IT!

        const gps_fix & fix = gps.fix();

        //  construct data to be sent to the OLED *****************************

        display.setTextSize(1);
        display.setTextColor(WHITE);

        display.setCursor(0, 0);
        display.print( F("Sat: "));

        if (fix.valid.satellites) {
          display.setCursor(30, 0);
          display.println( fix.satellites );
        }

        if (fix.valid.date && fix.valid.time) {
          display.setCursor(95, 0);
          NeoGPS::clock_t seconds = (NeoGPS::clock_t) fix.dateTime;     // convert pieces to seconds
          seconds -= 4 * 60 * 60;                                      // offset seconds
          NeoGPS::time_t localTime( seconds );                        // convert seconds back to pieces

          if (localTime.hours < 10) {
            display.print( '0' );
          }

          display.print( localTime.hours ); display.print( ':' ); // use pieces
          if (localTime.minutes < 10) {
            display.print( '0' );
          }

          display.print( localTime.minutes);

        }

        if (fix.valid.speed) {
          display.setTextSize(7);
          display.setCursor(23, 12);
          display.println( fix.speed_mph(), 0);
        }
        display.display();

      }
    }
  }
}
