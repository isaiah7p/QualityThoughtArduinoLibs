// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class using DMP (MotionApps v2.0)
// 6/21/2012 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib

//  GPS Module Code
// http://davidhoulding.blogspot.in/2014/06/gps-location-sensing-with-itead-gps.html

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include <SoftwareSerial.h>
#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file
#include "TinyGPS.h"
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>



////lcd2
//#define OLED_RESET 4
//Adafruit_SSD1306 lcd2(OLED_RESET);
//
//// OLED I2C bus address
//#define OLED_address  0x3c



// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
//MPU6050 mpu;
MPU6050 mpu(0x68); // <-- use for AD0 high
LiquidCrystal_I2C lcd2(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address



bool alertSMS = true;
int smsCount = 0;

float topGPSSpeed = 0;

TinyGPS gps;
//
int unoRxPin = 6; // connected to TX pin of the GPS
int unoTxPin = 7; // connected to RX pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);



// SIM Module setup
SoftwareSerial sim800l(10, 11); //RX - TX


int backLight = 13;    // pin 13 will control the backlight
//
long startMillis;
long secondsToFirstLocation = 0;

float flat = 0;
float flon = 0;


#define OUTPUT_READABLE_YAWPITCHROLL

//#define OUTPUT_READABLE_WORLDACCEL

// uncomment "OUTPUT_TEAPOT" if you want output that matches the
// format used for the InvenSense teapot demo
//#define OUTPUT_TEAPOT



#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
//#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float pitchVal;
float rollVal;
float yawVal;
float rangePitch = 45;
float rangeRoll = 45;
float rangeYaw = 15;
float gpsSpeed ;
int year;
byte month, day, hour, minute, second ;
// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };



// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}



// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  Serial.begin(115200);

  ss.begin(9600);

  // SIM Initial SetUp ...



  //
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  //
  //LCD SetUp
  lcd2.begin(16, 2);
  lcd2.clear();

  //  Welcome Note from DustDevils
  //  This Product have both Manual and Automated Alerts .
  //  Alarming even if u r unconcious after an accident .
  //

  lcd2.setCursor(0, 0);
  lcd2.print("|~~~~~~~~~~~~~~~~~~|" );

  //lcd2.setCursor(0, 1);
  //lcd2.print("|  Smart DD SOS    |" );

  //lcd2.setCursor(0, 2);
 // lcd2.print("| dustdevils.in/sos|" );

  //lcd2.setCursor(0, 3);

 // lcd2.print("|__________________|" );

  //  for (int i = 0 ; i < 4 ; i++) {
  //    lcd2.backlight();
  //    delay(250);
  //    lcd2.noBacklight();
  //    delay(250);
  //
  //  }
  //  lcd2.backlight();



  //lcd2 ACC
  //lcd2.println("DD Smart GPS");


  //  Wire.begin();

  //  Wire.beginTransmission(MPU);
  //  Wire.write(0x6B);  // PWR_MGMT_1 register
  //  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  //  Wire.endTransmission(true);

  startMillis = millis();

  pitchVal = 0;
  rollVal = 0;
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize serial communication
  // (115200 chosen because it is required for Teapot Demo output, but it's
  // really up to you depending on your project)

  while (!Serial); // wait for Leonardo enumeration, others continue immediately

  // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
  // Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
  // the baud timing being too misaligned with processor ticks. You must use
  // 38400 or slower in these cases, or use some kind of external separate
  // crystal solution for the UART timer.

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));



  //lcd2.print("Testing MPU6050Connection..... ");
  //lcd2.print(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // wait for ready
  //     Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  //      while (Serial.available() && Serial.read()); // empty buffer
  //      while (!Serial.available());                 // wait for data
  //      while (Serial.available() && Serial.read()); // empty buffer again

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  //lcd2.print("Initializing DMP...");
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    //lcd2.print(" Enabling interrupt detection (Arduino external interrupt 0 ...");
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));

    //lcd2.print("DMP ready! Waiting for first interrupt...");

    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));

    //lcd2.print("DMP Initialization failed (code ");
    //lcd2.print(devStatus);
  }

  // configure LED for output
  //pinMode(LED_PIN, OUTPUT);



} // setup ends here







// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {

  //   lcd2.lcd2();
  //lcd2.clear();   // clears the screen and buffer
  // PIX=GREEN; // colours of all lines drawn will be green until changed.


  //  Setting SMS Alerts to False by Default
  alertSMS = false;
  //  GPS Data Programming

  //lcd2.clear();

  //delay(1000);

  // if programming failed, don't try to do anything
  if (!dmpReady) return;

  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) {
    // other program behavior stuff here
    // .
    // .
    // .
    // if you are really paranoid you can frequently test in between other
    // stuff to see if mpuInterrupt is true, and if so, "break;" from the
    // while() loop to immediately process the MPU data
    // .
    // .
    // .
    //ss.listen();


  }


  //  delay(500);


  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1084) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    // lcd2.clear();
    //lcd2.print("FIFO overflow!");

    Serial.println(F("   FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

#ifdef OUTPUT_READABLE_QUATERNION
    // lcd2 quaternion values in easy matrix form: w x y z
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    Serial.print("quat\t");
    Serial.print(q.w);
    Serial.print("\t");
    Serial.print(q.x);
    Serial.print("\t");
    Serial.print(q.y);
    Serial.print("\t");
    Serial.println(q.z);
#endif

#ifdef OUTPUT_READABLE_EULER
    // lcd2 Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetEuler(euler, &q);
    Serial.print("euler\t");
    Serial.print(euler[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(euler[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.println(euler[2] * 180 / M_PI);
#endif

#ifdef OUTPUT_READABLE_YAWPITCHROLL

    delay(1000);

    // GPS Data Aquaring

    bool newData = false;
    unsigned long chars = 0;
    unsigned short sentences, failed;

    // For one second we parse GPS data and report some key values
    for (unsigned long start = millis(); millis() - start < 1000;)
    {
      while (ss.available())
      {
        int c = ss.read();
        ++chars;
        if (gps.encode(c)) // Did a new valid sentence come in?
          newData = true;
      }
    }

    if (newData)
    {
      // we have a location fix so output the lat / long and time to acquire
      if (secondsToFirstLocation == 0) {
        secondsToFirstLocation = (millis() - startMillis) / 1000;
      }

      // lcd2.clear();  // start with a blank screen

      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);
      gpsSpeed = gps.f_speed_kmph();

//      if (gpsSpeed >= topGPSSpeed) {
//
//        topGPSSpeed = gpsSpeed;
//
//
//      } else if (gpsSpeed >= topGPSSpeed) {
//        // do nothing
//      } else {
//        // do nothing
//      }


      // GPS Top Speed 
  //    Serial.print("Top Speed =");
  //    Serial.println(topGPSSpeed , 2);



      // lcd2.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
      Serial.print("Lat=");
      Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);

      //

      Serial.print("Long=");
      Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
      Serial.print("  !!!  GPS SPeed =");
      Serial.print(gpsSpeed);

      if (chars == 0) {
        // if you haven't got any chars then likely a wiring issue
       // lcd2.setCursor(0, 2);          // set cursor to column 0, row 0 (the first row)
        Serial.print("No GPS: check wiring");
      }
      else if (secondsToFirstLocation == 0) {
        // if you have received some chars but not yet got a fix then indicate still searching and elapsed time
        //lcd2.clear();  // start with a blank screen

        long seconds = (millis() - startMillis) / 1000;

        //lcd2.setCursor(0, 0);          // set cursor to column 0, row 0 (the first row)
       // lcd2.print("Searching ");
        for (int i = 0; i < seconds % 4; ++i) {
         // lcd2.print(".");
        }

        //lcd2.setCursor(0, 1);
        //lcd2.print("Elapsed time:");
        //lcd2.print(seconds);
        //lcd2.print("s");
      }

    }


    // lcd2 Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    Serial.print("ypr\t");
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.println(ypr[2] * 180 / M_PI);

    pitchVal = ypr[1] * 180 / M_PI ;
    rollVal = ypr[2] * 180 / M_PI;
    yawVal =  ypr[0] * 180 / M_PI;

    if ( pitchVal < rangePitch &&  pitchVal > -rangePitch && rollVal < rangeRoll && rollVal > -rangeRoll) {

      alertSMS = false;
      Serial.print("Alert SMS is :");
      Serial.print( alertSMS);
    //  lcd2.clear();


     // lcd2.setCursor(0, 0);
    //  lcd2.print(" DustDevils Smart AI");
    //  lcd2.print("Speed :"); lcd2.print(gpsSpeed); lcd2.print("kmph");

     // lcd2.setCursor(0 , 1);
    //  lcd2.print("YPR:");


     // lcd2.print(ypr[0] * 180 / M_PI);
    //  lcd2.print("#");
      //  lcd2.setCursor(0 , 2);
      //  lcd2.print("PITCH X :");
      //  lcd2.print("|");
    //  lcd2.print(ypr[1] * 180 / M_PI);

      //lcd2.setCursor(0 , 3);
      //lcd2.print("ROLL Y  :");
     // lcd2.print("#");
     // lcd2.print(ypr[2] * 180 / M_PI);
      //lcd2.setCursor(0 , 2);

     // lcd2.setCursor(0 , 2);
     // lcd2.print("Lat  :");
    //  lcd2.print(flat, 6);
     // lcd2.setCursor(0 , 3);
     // lcd2.print("long :");
     // lcd2.print(flon, 6);

      Serial.println("Rider Safe  With Pitch  & Roll  & Yaw  @ lat & long");
      Serial.println(pitchVal);
      Serial.println(rollVal);
      Serial.println(yawVal);
      Serial.println(flat, 6);
      Serial.println(flon, 6);

      delay(100);

    }

    if ( pitchVal > rangePitch ||  pitchVal < -rangePitch ) {
      alertSMS = true;
      if (flat != 0) {
        Serial.println("Rider Needs ur Help @ ");
        Serial.println(pitchVal);
        Serial.println(rollVal);

       // lcd2.clear();
       // lcd2.setCursor(0 , 0);
       // lcd2.print("Speed :"); lcd2.print(gpsSpeed); lcd2.print("kmph");
        // lcd2.print("DustDevils Product ");

        //lcd2.setCursor(0 , 1);
        //lcd2.print("Rider Needs ur Help@ ");
        // lcd2.print(pitchVal);
        Serial.println("Rider Needs ur Help @ ");
        Serial.println(pitchVal);


      //  lcd2.setCursor(0 , 2);
        //lcd2.print("maps.google.com/?q=");
        //lcd2.print(rollVal);

       // lcd2.setCursor(0 , 3);
        // lcd2.print("dustdevils.in/sos_id");

        //lcd2.print(flat, 6);
       // lcd2.print(",");
       // lcd2.print(flon, 6);  ///  google.co.in/maps/@flat,flon,16z or maps.google.com/?q=flat,flan


        Serial.print("maps.google.com/?q=");
        Serial.print(flat, 6);
        Serial.print(",");
        Serial.print(flon, 6);

//
//        for (int i = 0 ; i < 4 ; i++) {
//          lcd2.backlight();
//          delay(50);
//          lcd2.noBacklight();
//          delay(50);
//
//        }
//        lcd2.backlight();

      }

    }

    if ( rollVal > rangeRoll || rollVal < -rangeRoll ) {

      if (flat != 0) {

        Serial.println("Rider Needs ur Help @ ");
        Serial.println(pitchVal);
        Serial.println(rollVal);
      //  lcd2.clear();
       // lcd2.print("Speed :"); lcd2.print(gpsSpeed); lcd2.print("kmph");
        //lcd2.print("DustDevils Product ");

     //   lcd2.setCursor(0 , 1);
       // lcd2.print("Rider Needs ur Help @ ");
       // lcd2.print(rollVal);

        Serial.println("Rider Needs ur Help @ ");

        Serial.println(rollVal);

        //lcd2.setCursor(0 , 2);
        //lcd2.print("maps.google.com/?q=");
        //lcd2.print(rollVal);

        //lcd2.setCursor(0 , 3);
        // lcd2.print("dustdevils.in/sos_id");

        //lcd2.print(flat, 6);
        //lcd2.print(",");
        //lcd2.print(flon, 6);  ///  google.co.in/maps/@flat,flon,16z or maps.google.com/?q=flat,flan

        Serial.print("maps.google.com/?q=");
        Serial.print(flat, 6);
        Serial.print(",");
        Serial.print(flon, 6);



//        for (int i = 0 ; i < 4 ; i++) {
//          //lcd2.backlight();
//          delay(250);
//          lcd2.noBacklight();
//          delay(250);
//
//        }
//        lcd2.backlight();

        alertSMS = true;
      }
    }


    delay(200);


    if (alertSMS && ( flat != 0 && flon != 0)) {


      sim800l.begin(115200);

      //sim800l.listen();
      Serial.println("-- SUBBU -- Phone ");

      sim800l.println(F("AT"));
      delay(200);
      //Serial.println(debug());
      sim800l.println(F("AT+CBC"));
      delay(200);
      //Serial.println(debug());

      sim800l.println(F("AT+CSQ"));
      delay(200);

      sim800l.println(F("AT+CMGF=1"));
      delay(200);
      //if (res_at(debug(),"OK")){
      sim800l.println(F("AT+CMGS=\"+919160530312\""));//
      delay(200);
      // if(res_at(debug(),">")){
      sim800l.println("Emergency Help for Subash DD ,pls reach him  ");
      sim800l.print("maps.google.com/?q=");
      sim800l.print(flat, 6);
      sim800l.print(",");
      sim800l.print(flon, 6);
    //  sim800l.println(" HEALTH CARD  : 7869 7868 6778 1234");
      sim800l.println(pitchVal);
      sim800l.println(rollVal);
      sim800l.println("Speed:");
      sim800l.println(gpsSpeed);



      //sim800l.println("maps.google.com");
      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);
      delay(200);

      //// Emergency Contact to Isaiah : 

      //sim800l.listen();
      Serial.println("sim800...........");

      sim800l.println(F("AT"));
      delay(200);
      
      //Serial.println(debug());
      sim800l.println(F("AT+CBC"));
      delay(200);
      
      //Serial.println(debug());

      sim800l.println(F("AT+CSQ"));
      delay(200);

      sim800l.println(F("AT+CMGF=1"));
      delay(200);
      //if (res_at(debug(),"OK")){
      sim800l.println(F("AT+CMGS=\"+919676867575\""));//
      delay(200);
      // if(res_at(debug(),">")){
      sim800l.println("Emergency Help for Subash DD ,pls reach him  ");
      sim800l.print("maps.google.com/?q=");
      sim800l.print(flat, 6);
      sim800l.print(",");
      sim800l.print(flon, 6);
    //  sim800l.println(" HEALTH CARD  : 7869 7868 6778 1234");
      sim800l.println(pitchVal);
      sim800l.println(rollVal);
      sim800l.println("Speed:");
      sim800l.println(gpsSpeed);



      //sim800l.println("maps.google.com");
      delay(200);
      sim800l.println();
      delay(200);
      sim800l.write(0x1A);


      
      // env_sms();
      // i++;
      alertSMS = false;


      //      lcd2.println("SMS Generated ");
      //      for (int i = 0 ; i < 4 ; i++) {
      //        lcd2.backlight();
      //        delay(50);
      //        lcd2.noBacklight();
      //        delay(50);
      //
      //      }
      //      lcd2.backlight();
      // calling the emergency contacts

    //   hac_llam();

      // Update FACEBOOK through Security Code & URL

      // maps.google.com/?q=18.0276135,79.5088303

      //       sim800l.println(F("AT"));
      //      delay(200);
      //      //Serial.println(debug());
      //      sim800l.println(F("AT+CBC"));
      //      delay(200);
      //      //Serial.println(debug());
      //
      //      sim800l.println(F("AT+CSQ"));
      //      delay(200);
      //
      //      sim800l.println(F("AT+CMGF=1"));
      //      delay(200);
      //      //if (res_at(debug(),"OK")){
      //      sim800l.println(F("AT+CMGS=\"51555\""));//
      //      delay(200);
      //      // if(res_at(debug(),">")){
      //      sim800l.println("5267  Im in Emergency,pls reach me at below Location  ");
      //      sim800l.print("maps.google.com/?q=");
      //      sim800l.print(flat, 6);
      //      sim800l.print(",");
      //      sim800l.print(flon, 6);
      //
      //      sim800l.println(pitchVal);
      //      sim800l.println(rollVal);
      //
      //      delay(200);
      //      sim800l.println();
      //      delay(200);
      //      sim800l.write(0x1A);
      //      delay(200);
      //

    }
    //    delay(200);
    //        if ( yawVal > rangeYaw || yawVal < -rangeYaw ) {
    //      Serial.println("BIKE ALARMED @ ");
    //      Serial.println(pitchVal);
    //      Serial.println(rollVal);
    //      lcd2.clear();
    //      lcd2.print("DustDevils Product ");
    //
    //      lcd2.setCursor(0 , 1);
    //      lcd2.print("BIKE ALARMED @ ");
    //
    //      Serial.println("BIKE ALARMED @ ");
    //      Serial.println(pitchVal);
    //      Serial.println(rollVal);
    //      Serial.println(yawVal);
    //
    //      lcd2.setCursor(0 , 2);
    //      lcd2.print("maps.google.com/?q=");
    //      //lcd2.print(rollVal);
    //
    //      lcd2.setCursor(0 , 3);
    //      // lcd2.print("dustdevils.in/sos_id");
    //
    //      lcd2.print(flat, 6);
    //      lcd2.print(",");
    //      lcd2.print(flon, 6);  ///  google.co.in/maps/@flat,flon,16z or maps.google.com/?q=flat,flan
    //
    //      Serial.print("maps.google.com/?q=");
    //      Serial.print(flat);
    //      Serial.print(",");
    //      Serial.print(flon);
    //
    //    }
    //delay(200);

#endif

#ifdef OUTPUT_READABLE_REALACCEL
    // lcd2 real acceleration, adjusted to remove gravity
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    Serial.print("areal\t");
    Serial.print(aaReal.x);
    Serial.print("\t");
    Serial.print(aaReal.y);
    Serial.print("\t");
    Serial.println(aaReal.z);
#endif

#ifdef OUTPUT_READABLE_WORLDACCEL
    // lcd2 initial world-frame acceleration, adjusted to remove gravity
    // and rotated based on known orientation from quaternion
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
    Serial.print("aworld\t");
    Serial.print(aaWorld.x);
    Serial.print("\t");
    Serial.print(aaWorld.y);
    Serial.print("\t");
    Serial.println(aaWorld.z);
#endif

#ifdef OUTPUT_TEAPOT
    // lcd2 quaternion values in InvenSense Teapot demo format:
    teapotPacket[2] = fifoBuffer[0];
    teapotPacket[3] = fifoBuffer[1];
    teapotPacket[4] = fifoBuffer[4];
    teapotPacket[5] = fifoBuffer[5];
    teapotPacket[6] = fifoBuffer[8];
    teapotPacket[7] = fifoBuffer[9];
    teapotPacket[8] = fifoBuffer[12];
    teapotPacket[9] = fifoBuffer[13];
    Serial.write(teapotPacket, 14);
    teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
#endif

    // blink LED to indicate activity
    blinkState = !blinkState;
   // digitalWrite(LED_PIN, blinkState);
  }

  //  RenderImage(); // go draw it!


}

void hac_llam() {
  //sim800l.listen();
  sim800l.println(F("ATD+919676867575;"));
  delay(500);
  Serial.println("Calling IN_CASE_OF_EMERGENCY_NUMBERS");
}

/***********************************************************************************************************************************/

