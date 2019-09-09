#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial GPS(6,7); // configure software serial port 

// Create an instance of the TinyGPS object
TinyGPS shield;

void setup()
{
  GPS.begin(9600);
  Serial.begin(9600);
  Serial.println("SetUp");
}

// The getgps function will interpret data from GPS and display on serial monitor
void getgps(TinyGPS &gps)
{
   Serial.println("getgps method");
  // Define the variables that will be used
  float latitude, longitude;
  // Then call this function
  shield.f_get_position(&latitude, &longitude);
 // Serial.println("--------------------------------------------------------------");
  Serial.print("Lat: "); 
  Serial.print(latitude,5); 
  Serial.print(" Long: "); 
  Serial.println(longitude,5);
//
//  int year;
//  byte month, day, hour, minute, second, hundredths;
//  shield.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
//
//  // Print data and time
//  Serial.print("GMT - ");
//  Serial.print(hour, DEC);
//  Serial.print(":");
//  if (minute<10)
//  {
//    Serial.print("0");
//    Serial.print(minute, DEC);
//  } 
//  else if (minute>=10)
//  {
//    Serial.print(minute, DEC);
//  }
//  Serial.print(":");
//  if (second<10)
//  {
//    Serial.print("0");
//    Serial.print(second, DEC);
//  } 
//  else if (second>=10)
//  {
//    Serial.print(second, DEC);
//  }
//  Serial.print(" ");
//  Serial.print(day, DEC);
//  Serial.print("/");
//  Serial.print(month, DEC);
//  Serial.print("/");
//  Serial.println(year, DEC);
//  Serial.print("Altitude ");
//  Serial.print(gps.f_altitude());
//  Serial.print("m ");
//  Serial.print(gps.f_speed_kmph());
//  Serial.println("km/h");
}

void loop()
{
    
  byte a;
  if ( GPS.available() > 0 ) // if there is data coming from the GPS shield
  {  
    a = GPS.read(); // get the byte of data
    if(shield.encode(a)) // if there is valid GPS data...
    {  
      getgps(shield); // then grab the data and display it on the LCD
    }
  }
}
