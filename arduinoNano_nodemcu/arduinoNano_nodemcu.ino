// Arduino Nano 
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library

#include <Wire.h>

IRTherm therm; // Create an IRTherm object to interact with throughout

const byte LED_PIN = 8; // Optional LED attached to pin 8 (active low)



int hr = 67;
int ecg = 234;
int temp = 97;
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
int sensorpowerPin = 6;           // pin to switch on to power the sensor
int buttonPin = 10;               // pin for the on/off button

int longpress_len = 3;           // length for long-pressing button


// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, must be seeded! 
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// for switching on/off via button
enum { EV_NONE=0, EV_SHORTPRESS, EV_LONGPRESS };
boolean button_was_pressed; // previous state
int button_pressed_counter; // press running duration
boolean sensor_is_running;  // sensor on?



void setup() {
   Serial.begin(9600);           /* start serial for debug */
    pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -

  pinMode(sensorpowerPin,OUTPUT);   // pin that will provide power for the sensor
  digitalWrite(sensorpowerPin, LOW);
  sensor_is_running = false;
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); // connect internal pull-up
  button_was_pressed = false;
  button_pressed_counter = 0;
  
  //Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 

  therm.begin(); // Initialize thermal IR sensor
  therm.setUnit(TEMP_F); // Set the library's units to Farenheit
  if (therm.read()){
    // Use the object() and ambient() functions to grab the object and ambient
 // temperatures.
  // They'll be floats, calculated out to the unit you set with setUnit().
   // Serial.print("Object: " + String(therm.object(), 2));
    temp = therm.object();
    
//    Serial.println("temp ::");
//    Serial.println(temp);
  }
 // Serial.println("Setup b4 wire ");
 
 
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 //Serial.println("Setup done ");

}



int handle_button()
{
  int event;
  int button_now_pressed = !digitalRead(buttonPin); // pin low -> pressed

  if (!button_now_pressed && button_was_pressed) {
    if (button_pressed_counter < longpress_len)
      event = EV_SHORTPRESS;
    else
      event = EV_LONGPRESS;
  }
  else
    event = EV_NONE;

  if (button_now_pressed)
    ++button_pressed_counter;
  else
    button_pressed_counter = 0;

  button_was_pressed = button_now_pressed;
  return event;
}



void loop() {
   
    if (sensor_is_running) {
    sendDataToProcessing('S', Signal);     // send Processing the raw Pulse Sensor data
    if (QS == true){                       // Quantified Self flag is true when arduino finds a heartbeat
          fadeRate = 255;                  // Set 'fadeRate' Variable to 255 to fade LED with pulse
          sendDataToProcessing('B',BPM);   // send heart rate with a 'B' prefix
          sendDataToProcessing('Q',IBI);   // send time between beats with a 'Q' prefix
          QS = false;                      // reset the Quantified Self flag for next time    
       }
    
    ledFadeToBeat();
  }
  hr=BPM;
//  Serial.println("Heart Rate :");
//  Serial.println(hr);
  boolean event = handle_button();
  if (event==EV_LONGPRESS) {  // toggle state of 
    if (sensor_is_running) {
      digitalWrite(sensorpowerPin, LOW);
      sensor_is_running = false;
    }
    else {
      digitalWrite(sensorpowerPin, HIGH);      
      sensor_is_running = true;
    }
  }
 
 delay(10);
 //Serial.println("loop ");

 if (therm.read()){
    // Use the object() and ambient() functions to grab the object and ambient
 // temperatures.
  // They'll be floats, calculated out to the unit you set with setUnit().
    //Serial.print("Object: " + String(therm.object(), 2));
    temp = therm.object();
//    Serial.write('°'); // Degree Symbol
//    Serial.println("F");
//    Serial.print("Ambient: " + String(therm.ambient(), 2));
//    Serial.write('°'); // Degree Symbol
//    Serial.println("F");
//    Serial.println();
  }   
  // ECG Calculations : 

    // send the value of analog input 0:
    ecg = analogRead(A1);
//    Serial.println("ecg:");
//    Serial.println(ecg);
  

 Wire.write(hr); 

 Wire.write(ecg);
 
  Wire.write(temp);
  
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    //Serial.print(c);           /* print the character */
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
 //Wire.begin(8);
 //Serial.print(hr);  
 
 Wire.write(hr); 
 
  //Serial.print(hr);
  
  Wire.write(ecg);
  
 // Serial.print(ecg);
  
  Wire.write(temp);
  
  //Serial.print(temp); 
}



void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }


void sendDataToProcessing(char symbol, int data ){
  //  Serial.print(symbol);                // symbol prefix tells Processing what type of data is coming
   // Serial.println(data);                // the data to send culminating in a carriage return
  }

volatile int rate[10];                    // array to hold last ten IBI values
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find IBI
volatile int P =512;                      // used to find peak in pulse wave, seeded
volatile int T = 512;                     // used to find trough in pulse wave, seeded
volatile int thresh = 512;                // used to find instant moment of heart beat, seeded
volatile int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM


void interruptSetup(){     
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x06;     // DON'T FORCE COMPARE, 256 PRESCALER 
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED      
} 


// THIS IS THE TIMER 2 INTERRUPT SERVICE ROUTINE. 
// Timer 2 makes sure that we take a reading every 2 miliseconds
ISR(TIMER2_COMPA_vect){                         // triggered when Timer2 counts to 124
  cli();                                      // disable interrupts while we do this
  Signal = analogRead(pulsePin);              // read the Pulse Sensor 
  sampleCounter += 2;                         // keep track of the time in mS with this variable
  int N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise

    //  find the peak and trough of the pulse wave
  if(Signal < thresh && N > (IBI/5)*3){       // avoid dichrotic noise by waiting 3/5 of last IBI
    if (Signal < T){                        // T is the trough
      T = Signal;                         // keep track of lowest point in pulse wave 
    }
  }

  if(Signal > thresh && Signal > P){          // thresh condition helps avoid noise
    P = Signal;                             // P is the peak
  }                                        // keep track of highest point in pulse wave

  //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
  // signal surges up in value every time there is a pulse
  if (N > 250){                                   // avoid high frequency noise
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){        
      Pulse = true;                               // set the Pulse flag when we think there is a pulse
      digitalWrite(blinkPin,HIGH);                // turn on pin 13 LED
      IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
      lastBeatTime = sampleCounter;               // keep track of time for next pulse

      if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
        secondBeat = false;                  // clear secondBeat flag
        for(int i=0; i<=9; i++){             // seed the running total to get a realisitic BPM at startup
          rate[i] = IBI;                      
        }
      }

      if(firstBeat){                         // if it's the first time we found a beat, if firstBeat == TRUE
        firstBeat = false;                   // clear firstBeat flag
        secondBeat = true;                   // set the second beat flag
        sei();                               // enable interrupts again
        return;                              // IBI value is unreliable so discard it
      }   


      // keep a running total of the last 10 IBI values
      word runningTotal = 0;                  // clear the runningTotal variable    

      for(int i=0; i<=8; i++){                // shift data in the rate array
        rate[i] = rate[i+1];                  // and drop the oldest IBI value 
        runningTotal += rate[i];              // add up the 9 oldest IBI values
      }

      rate[9] = IBI;                          // add the latest IBI to the rate array
      runningTotal += rate[9];                // add the latest IBI to runningTotal
      runningTotal /= 10;                     // average the last 10 IBI values 
      BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
      hr=BPM;
      //Serial.println(BPM);
      QS = true;                              // set Quantified Self flag 
      // QS FLAG IS NOT CLEARED INSIDE THIS ISR
    }                       
  }

  if (Signal < thresh && Pulse == true){   // when the values are going down, the beat is over
    digitalWrite(blinkPin,LOW);            // turn off pin 13 LED
    Pulse = false;                         // reset the Pulse flag so we can do it again
    amp = P - T;                           // get amplitude of the pulse wave
    thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
    P = thresh;                            // reset these for next time
    T = thresh;
  }

  if (N > 2500){                           // if 2.5 seconds go by without a beat
    thresh = 512;                          // set thresh default
    P = 512;                               // set P default
    T = 512;                               // set T default
    lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date        
    firstBeat = true;                      // set these to avoid noise
    secondBeat = false;                    // when we get the heartbeat back
  }

  sei();                                   // enable interrupts when youre done!
}// end isr


