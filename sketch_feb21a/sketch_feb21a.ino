
int analogPin = A10; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val = 0;  // variable to store the value read

void setup() {
  Serial.begin(9600);           //  setup serial
}

void loop() {
  val = analogRead(analogPin);  // read the input pin
  Serial.print(val);          // debug value
  getTemp();
}

  void getTemp(){
    Serial.println("Test UIssues ");
    }
