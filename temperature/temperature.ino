#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>

 Adafruit_MLX90614 mlx = Adafruit_MLX90614();


void setup() 
{
  Serial.begin(9600);
  mlx.begin(); 

}

void loop() 
{

  Serial.print("*F\tObject = "); 
  Serial.print(mlx.readObjectTempF()/19.265618661257606); 
  Serial.println("*F");
 
  Serial.println();
  delay(1000);
}

