// Robo India Tutorial 
// Digital Output on LED 
// Hardware: NodeMCU Blynk Board


#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "378bd77a0dda46dfb1c13a57c9baeda8";            // You should get Auth Token in the Blynk App.
                                           // Go to the Project Settings (nut icon).
char ssid[] = "NETGEAR68";    // Your WiFi credentials.
char pass[] = "Quality@qt";  // Set password to "" for open networks.

float heartrate = 0;



void setup()
{
    Serial.begin(9600);// Debug console
    Blynk.begin(auth, ssid, pass);
  
}

void loop()
{ 
  
  heartrate = analogRead(A0);

  Serial.println(heartrate);
  delay(800);
   Blynk.virtualWrite(V0, heartrate);
   
 // Blynk.virtualWrite(V1, h);
  
  Blynk.run();
  
}

