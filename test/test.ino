#include <Arduino.h> 
#include <EEPROM.h> 
#define USE_SERIAL Serial
#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>

// Variable init
const int buttonPin = D2; // variable for D2 pin
const int ledPin = D7;
char push_data[200]; //string used to send info to the server ThingSpeak
int addr = 0; //endereço eeprom
byte sensorInterrupt = 0; // 0 = digital pin 2

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

volatile byte pulseCount;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

//SSID and PASSWORD for the AP (swap the XXXXX for real ssid and password )
const char * ssid = "DustDevils";
const char * password = "b4b3c69bb4b3c69b5267!";

//HTTP client init
HTTPClient http;

void setup() {
    Serial.begin(115200); // Start the Serial communication to send messages to the computer
    delay(10);
    Serial.println('\n');

    startWIFI();
  
    // Initialization of the variable “buttonPin” as INPUT (D2 pin)
    pinMode(buttonPin, INPUT);
  
    // Two types of blinking
    // 1: Connecting to Wifi
    // 2: Push data to the cloud
    pinMode(ledPin, OUTPUT); 
    
    pulseCount = 0;
    flowRate = 0.0;
    flowMilliLitres = 0;
    totalMilliLitres = 0;
    oldTime = 0;

    digitalWrite(buttonPin, HIGH);
    attachInterrupt(digitalPinToInterrupt(buttonPin), pulseCounter, RISING);

}

void loop() {
    if (WiFi.status() == WL_CONNECTED && (millis() - oldTime) > 1000) // Only process counters once per second
    {
        // Disable the interrupt while calculating flow rate and sending the value to
        // the host
        detachInterrupt(sensorInterrupt);

        // Because this loop may not complete in exactly 1 second intervals we calculate
        // the number of milliseconds that have passed since the last execution and use
        // that to scale the output. We also apply the calibrationFactor to scale the output
        // based on the number of pulses per second per units of measure (litres/minute in
        // this case) coming from the sensor.
        flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;

        // Note the time this processing pass was executed. Note that because we've
        // disabled interrupts the millis() function won't actually be incrementing right
        // at this point, but it will still return the value it was set to just before
        // interrupts went away.
        oldTime = millis();

        // Divide the flow rate in litres/minute by 60 to determine how many litres have
        // passed through the sensor in this 1 second interval, then multiply by 1000 to
        // convert to millilitres.
        flowMilliLitres = (flowRate / 60) * 1000;

        // Add the millilitres passed in this second to the cumulative total
        totalMilliLitres += flowMilliLitres;

        unsigned int frac;

        // Print the flow rate for this second in litres / minute
        Serial.print("Flow rate: ");
        Serial.print(int(flowRate)); // Print the integer part of the variable
        Serial.print("."); // Print the decimal point
        // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
        frac = (flowRate - int(flowRate)) * 10;
        Serial.print(frac, DEC); // Print the fractional part of the variable
        Serial.print("L/min");
        // Print the number of litres flowed in this second
        Serial.print("  Current Liquid Flowing: "); // Output separator
        Serial.print(flowMilliLitres);
        Serial.print("mL/Sec");

        // Print the cumulative total of litres flowed since starting
        Serial.print("  Output Liquid Quantity: "); // Output separator
        Serial.print(totalMilliLitres);
        Serial.println("mL");

        if (flowRate > 0) {
            digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(100);          

            // Replace <YOUR_API_KEY> with your EmonCMS API Key 
        //    https://emoncms.org/input/post?node=emontx&fulljson={"power1":100,"power2":200,"power3":300}&apikey=3986278469e05747ca7b6d4b7c39353a
            sprintf(push_data, "http://emoncms.org/input/post?json={frac:%d.%d,flowml:%d,totalml:%d}&node=emontx&apikey=3986278469e05747ca7b6d4b7c39353a", int(flowRate), int(frac), flowMilliLitres, totalMilliLitres);
            Serial.printf("%s\n", push_data);
            http.begin(push_data);
            digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
            delay(100);              
            int httpCode = http.GET();
            // httpCode_code will be a negative number if there is an error
            Serial.print(httpCode);
            if (httpCode > 0) {
                digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
                delay(100);              
                // file found at server
                if (httpCode == HTTP_CODE_OK) {
                    String payload = http.getString();
                    Serial.print(" ");
                    Serial.print(payload);
                }
                digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
                delay(100);              
            } else {
                Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
        }
        // Reset the pulse counter so we can start incrementing again
        pulseCount = 0;

        // Enable the interrupt again now that we've finished sending output
        attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    } else if (WiFi.status() != WL_CONNECTED) {
        startWIFI();
    }
}

/*
Insterrupt Service Routine
 */
void pulseCounter() {
    // Increment the pulse counter
    pulseCount++;
}

void startWIFI(void) {
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);              
    
    WiFi.begin(ssid, password); // Connect to the network
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ...");
    oldTime = 0;
    int i = 0;
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
    delay(100);         
    
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(2000);
        Serial.print(++i);
        Serial.print('.');
        digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
        delay(100);  
    }
    delay(2000);
    Serial.print('\n');
    Serial.print("Connection established!");
    Serial.print("IP address:\t");
    Serial.print(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

}
