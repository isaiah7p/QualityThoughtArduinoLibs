#include <Wire.h>
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library
int UpperThreshold = 518;
int LowerThreshold = 490;
    int reading = 0;
    float BPM = 0.0;
    bool IgnoreReading = false;
    bool FirstPulseDetected = false;
    unsigned long FirstPulseTime = 0;
    unsigned long SecondPulseTime = 0;
    unsigned long PulseInterval = 0;

IRTherm therm; // Create an IRTherm object to interact with throughout

const byte LED_PIN = 8; 
void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);  
 therm.begin();  
 therm.setUnit(TEMP_C);/* start serial for debug */
 pinMode(10,INPUT);
  pinMode(11,INPUT);
}

void loop() {
 delay(100);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {

    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
  
  float hr  = 0;

  //Heart Rate Begin 

    reading = analogRead(0); 
      if(reading > UpperThreshold && IgnoreReading == false){
        if(FirstPulseDetected == false){
          FirstPulseTime = millis();
          FirstPulseDetected = true;
        }
        else{
          SecondPulseTime = millis();
          PulseInterval = SecondPulseTime - FirstPulseTime;
          FirstPulseTime = SecondPulseTime;
        }
        IgnoreReading = true;
      }
      if(reading < LowerThreshold){
        IgnoreReading = false;
      }  

      BPM = (1.0/PulseInterval) * 60.0 * 1000; 
      hr = BPM;  
       // uncomment these lines in case you want to view the various values in the console.....
      /*Serial.print(reading);
      Serial.print("\t");
      Serial.print(PulseInterval);
      Serial.print("\t");*/
      Serial.println(BPM);
   //   Serial.println(" BPM");
      Serial.flush();
      
  // HR End 
 // float ecg = 256;
 float temp = 0;

 // TEMP START 
   // Call therm.read() to read object and ambient temperatures from the sensor.
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    // Use the object() and ambient() functions to grab the object and ambient
 // temperatures.
  // They'll be floats, calculated out to the unit you set with setUnit().
    Serial.print("Object: " + String(therm.object(), 2));
    temp=therm.object();
    Serial.write('°'); // Degree Symbol
    Serial.println("C");
    Serial.print("Ambient: " + String(therm.ambient(), 2));
    Serial.write('°'); // Degree Symbol
    Serial.println("C");
    Serial.println();
  }
  
 // TEMP END 


 // ECG START 
  int ecg =0;
  if((digitalRead(10)==1)||(digitalRead(11)==1)){
      Serial.println("Gagal");
  }
  else{
      Serial.println(analogRead(A1));
      ecg=analogRead(A1);
  }
  delay(100);

 
 //ECG END 
 char mySensVal[4] = { hr,ecg ,temp}; 
 
 
  Wire.write(mySensVal); 
  //Wire.write("Hello NodeMCU");  /*send string on request */
  
}
void setLED(bool on)
{
  if (on)
    digitalWrite(LED_PIN, LOW);
  else
    digitalWrite(LED_PIN, HIGH);
}
