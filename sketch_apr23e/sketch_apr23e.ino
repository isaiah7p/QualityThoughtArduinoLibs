// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 


//#include <FreqMeasure.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"


const int sensorPin = A0;
int sensorVal;
float frequency;
float BMP;


PulseOximeter pox;
unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
 //FreqMeasure.begin();
 pox.begin();

  
}
double sum=0;
int count=0;

void loop() {
  
pox.update();  
       
        sensorVal = analogRead(sensorPin);
        Serial.println(sensorVal); 
        double voltage = convertToVoltage(sensorVal);
        
        double absorbance = calculateAbsorbance(voltage);
        double hr = pox.getHeartRate();
        double spo2 = pox.getSpO2();
         Serial.println(absorbance); 
          Serial.println(hr); 
          Serial.println(spo2); 
          

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


