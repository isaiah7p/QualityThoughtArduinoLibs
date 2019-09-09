#include <OneWire.h>
#include <DallasTemperature.h>

#define ONEWIRE_PIN 12
#define UPDATE_DELAY  5000

OneWire oneWire(ONEWIRE_PIN);
DallasTemperature sensors(&oneWire);

boolean TempSensorAvailable = false;

DeviceAddress TempSensor;
float tempC, tempF; // sensor values
int sensorNum = 100 ; // to tell sensors apart if you plan to log data from more than one 
int logNum = 0;  //log file counter



void setup() {

  Serial.begin(115200);
  delay(10);

 
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" OneWire device(s).");

  // report parasite power requirements
  Serial.print("Parasite power: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  if (!sensors.getAddress(TempSensor, 0)) {
    Serial.println("No OneWire Device Found");
  } else {
    TempSensorAvailable = true;
    Serial.println("OneWire Device Found");
    sensors.setResolution(TempSensor, 12);
  }
}

void loop() {
  String logfile;
  sensors.requestTemperatures();          // Get temprature
  tempC = sensors.getTempC(TempSensor);   // save temprature
  tempF = DallasTemperature::toFahrenheit(tempC);
  
  Serial.print("Temp C: ");
  Serial.println(tempC);        // Serial print the C  temperature
  Serial.print("Temp F: ");
  Serial.print(tempF);  // Convert then Serial print the F  temperature
  Serial.println("");

  
    delay(UPDATE_DELAY);  // Some delay
  
}


