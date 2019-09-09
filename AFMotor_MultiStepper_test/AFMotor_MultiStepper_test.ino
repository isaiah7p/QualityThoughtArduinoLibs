// MultiStepper
// -*- mode: C++ -*-
//
// Control both Stepper motors at the same time with different speeds
// and accelerations. 
// Requires the AFMotor library (https://github.com/adafruit/Adafruit-Motor-Shield-library)
// And AccelStepper with AFMotor support (https://github.com/adafruit/AccelStepper)
// Public domain!

#include <AccelStepper.h>
#include <AFMotor.h>

// two stepper motors one on each port
AF_Stepper motor1(200, 1);
AF_Stepper motor2(200, 2);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  motor1.onestep(FORWARD, SINGLE);
}
void backwardstep1() {  
  motor1.onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  motor2.onestep(FORWARD, SINGLE);
}
void backwardstep2() {  
  motor2.onestep(BACKWARD, SINGLE);
}

// Motor shield has two motor ports, now we'll wrap them in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);

void setup()
{  
  Serial.begin(9600);
    stepper1.setMaxSpeed(200.0);
    stepper1.setAcceleration(100.0);
    stepper1.moveTo(24);
    
    stepper2.setMaxSpeed(300.0);
    stepper2.setAcceleration(100.0);
    stepper2.moveTo(1000000);
    
}

void loop()
{ 

  
  if(Serial.available() > 0)
  {
    char data;
    data = Serial.read();
    Serial.write(Serial.read());

    switch (data)
    {   
      case '1': //FORWARD
        stepper1.run();
        stepper2.run();
//        analogWrite(Motor_B_Enable, 100);
//        analogWrite(Motor_A_Enable, 100);
//        digitalWrite(Motor_A_Reverse, LOW);
//        digitalWrite(Motor_B_Reverse, LOW);
//        digitalWrite(Motor_A_Forward, HIGH);
//        digitalWrite(Motor_B_Forward, HIGH);
        break;
      case '2': //REVERSE
        
    stepper1.run();
    stepper2.run();
//        analogWrite(Motor_B_Enable, 100);
//        analogWrite(Motor_A_Enable, 100);
//        digitalWrite(Motor_A_Forward, LOW);
//        digitalWrite(Motor_B_Forward, LOW);
//        digitalWrite(Motor_A_Reverse, HIGH);
//        digitalWrite(Motor_B_Reverse, HIGH);
        break;
      case '3': //FORWARD LEFT

       stepper1.run();
       
//        analogWrite(Motor_A_Enable, 100);
//        analogWrite(Motor_B_Enable, 0);
//        digitalWrite(Motor_A_Reverse, LOW);
//        digitalWrite(Motor_A_Forward, HIGH);
        break;
      case '4': //FORWARD RIGHT

      stepper2.run();

//      
//        analogWrite(Motor_B_Enable, 100);
//        analogWrite(Motor_A_Enable, 0);
//        digitalWrite(Motor_B_Reverse, LOW);
//        digitalWrite(Motor_B_Forward, HIGH);
        break;
      case '5': //REVERSE LEFT
      stepper2.run();
//        analogWrite(Motor_A_Enable, 100);
//        analogWrite(Motor_B_Enable, 0);
//        digitalWrite(Motor_A_Reverse, HIGH);
//        digitalWrite(Motor_A_Forward, LOW);
        break;
      case '6': //REVERSE RIGHT
      stepper1.run();
//        analogWrite(Motor_B_Enable, 100);
//        analogWrite(Motor_A_Enable, 0);
//        digitalWrite(Motor_B_Reverse, HIGH);
//        digitalWrite(Motor_B_Forward, LOW);
        break;
      default: //If bluetooth module receives any value not listed above, both motors turn off
//        analogWrite(Motor_A_Enable, 0);
//        analogWrite(Motor_B_Enable, 0);
        stepper1.run();
    }
  }
    // Change direction at the limits
//    if (stepper1.distanceToGo() == 0)
//	stepper1.moveTo(-stepper1.currentPosition());
//    stepper1.run();
//    stepper2.run();
}
