
const int sensorPin=A0;
int val =0;
int buzzerPin = 4;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Set Up ");
}

void loop() {
  // put your main code here, to run repeatedly:
val = analogRead(sensorPin);
Serial.println(" Sensor Val :  ");
Serial.print(val); 
if(val>300){
          tone( buzzerPin, 100, 1000);
  }
delay(2000);
}
