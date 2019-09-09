#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long CurrentValue = 0;
unsigned long StoredCode = 0;
const int buttonPin = 6; // the number of the pushbutton pin
const int ledPin = 4; // the number of the LED pin
const int outputPin = 3; // the number of the output LED pin
const int relayPin = 2; // the number of the relay pin
int buttonState = 0; // variable for reading the pushbutton status
int RecordState = 0; //is the reciever in record mode
int outputState = 1; //is the output on or off
void setup()
{
Serial.begin(9600);
irrecv.enableIRIn(); // Start the receiver
// initialize the LED pin as an output:
pinMode(ledPin, OUTPUT);
// initialize the pushbutton pin as an input:
pinMode(outputPin, OUTPUT);
// initialize the pushbutton pin as an input: pinMode(buttonPin, INPUT);
pinMode(relayPin, OUTPUT);
// initialize the pushbutton pin as an input: pinMode(buttonPin, INPUT);
}
void loop() {
// read the state of the pushbutton value:
buttonState = digitalRead(buttonPin);
// if a signal is detected, store the value
if (irrecv.decode(&results)) {
CurrentValue = (results.value);
// if the recieved value equals the programed value, then toggle the output state
if(CurrentValue == StoredCode) {
  outputState = !outputState;
}
// if the record mode is activated store the current value as the programed value
if (RecordState == 1) {
StoredCode = CurrentValue;
RecordState = 0;
digitalWrite(ledPin, LOW);  
Serial.println(StoredCode);  //displays stored code for reference
}
// Receive the next value
irrecv.resume();
}
else //if no signal is detected, then the current value is 0
{
CurrentValue = 0;
}
// check if the record button is pressed.
// if it is, the buttonState is HIGH:
if (buttonState == HIGH) {
//wait for the button to be released
while (buttonState == HIGH) {
buttonState = digitalRead(buttonPin);
}
//turn on the LED to indicate that record mode is on
digitalWrite(ledPin, HIGH); 
RecordState = 1;
}
//set the appropriate output state
if(outputState == 1) {
  digitalWrite(outputPin, HIGH);
  digitalWrite(relayPin, HIGH);
}
else {
    digitalWrite(outputPin, LOW);
    digitalWrite(relayPin, LOW);
}
}
