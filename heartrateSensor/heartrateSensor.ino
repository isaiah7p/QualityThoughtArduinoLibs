// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
//#define CAYENNE_PRINT Serial
//#include <CayenneMQTTESP8266.h>
//#include <FreqMeasure.h>

// WiFi network info.
//char ssid[] = "DustDevils";
//char wifiPassword[] = "b4b3c69b";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
//char username[] = "a2b9c680-f051-11e6-8577-0128e408a1ba";
//char password[] = "e6c693f5984eae6afaaf121e9726fb6ae663c378";
//char clientID[] = "ab197130-65a5-11e7-8378-e1a615c9f526";


const int sensorPin = A0;
int sensorVal;
float frequency;
float BMP;

PulseOximeter pox;
unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
 //FreqMeasure.begin();
 //pox.begin();

  //Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}
double sum=0;
int count=0;

void loop() {
 // Cayenne.loop();
pox.update();  
  //Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
  //if (millis() - lastMillis > 10000) {
  //  lastMillis = millis();
    //Write data to Cayenne here. This example just sends the current uptime in milliseconds.
    //Cayenne.virtualWrite(0, lastMillis);
    //Some examples of other functions you can use to send data.
    //Cayenne.celsiusWrite(1, 22.0);
    //Cayenne.luxWrite(2, 700);
    //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
  //  unsigned long timer = millis();
  

  
      
        
        sensorVal = analogRead(sensorPin);
        Serial.println(sensorVal); 
        double voltage = convertToVoltage(sensorVal);
        
        double absorbance = calculateAbsorbance(voltage);
        double hr = pox.getHeartRate()
        double spo2 = pox.getSpO2()
         Serial.println(absorbance); 
       // displayPulseInLabVIEW(absorbance, BMP);
       // Cayenne.virtualWrite(0, absorbance);
        //small delay to change our sampling rate
        //and stabilize our signal
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

//
////Default function for processing actuator commands from the Cayenne Dashboard.
////You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
//CAYENNE_IN_DEFAULT()
//{
//  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
//  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
//}
