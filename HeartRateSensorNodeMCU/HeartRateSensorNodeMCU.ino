#include <CayenneMQTTESP8266.h>
//#include <FreqMeasure.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define CAYENNE_PRINT Serial
// WiFi network info.
char ssid[] = "WARLOCK";
char wifiPassword[] = "P@ssw0rdiot";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "6fff5240-f05c-11e6-a971-4db18559717d";
char password[] = "4a5495303e20c8e904dab1862802bb32990cd994";
char clientID[] = "9f4b7f10-46ff-11e8-8927-a713813a39dc";
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const int sensorPin = A0;
int sensorVal;
float frequency;
float BMP;


PulseOximeter pox;
unsigned long lastMillis = 0;

void setup() {
	Serial.begin(9600);
 //FreqMeasure.begin();
 mlx.begin();  
 
 pox.begin();

	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}
double sum=0;
int count=0;

void loop() {
	Cayenne.loop();
pox.update();  
	  
        sensorVal = analogRead(sensorPin);
        Serial.println(sensorVal); 
        double voltage = convertToVoltage(sensorVal);
        
        double absorbance = calculateAbsorbance(voltage);
        double hr = pox.getHeartRate();
        double spo2 = pox.getSpO2();
         Serial.println(absorbance); 
         
      Serial.print("Object = "); 
      Serial.print(mlx.readObjectTempC()/10); 
      Serial.println("*C");

       // displayPulseInLabVIEW(absorbance, BMP);
        Cayenne.virtualWrite(0, absorbance);
        //small delay to change our sampling rate
        //and stabilize our signal
        Cayenne.virtualWrite(1, mlx.readObjectTempC()/10);
       // Cayenne.virtualWrite(2, spo2);
        Cayenne.virtualWrite(2,sensorVal/10 );
        delay(250);  
	
}

double convertToVoltage(double ADC_Val)
{
  double volt = 0;
  
  volt = 5*(ADC_Val/1023);
  
  return volt;
}

double calculateAbsorbance(double volt)
{
  double absorbance = 0;
  
  absorbance = log10(5/volt);
  
  return absorbance;  
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
