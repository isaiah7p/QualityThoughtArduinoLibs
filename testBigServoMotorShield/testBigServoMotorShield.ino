// simple stepper motor control 
// only x axis is used for dolly
#define EN 8 // stepper motor enable
#define X_DIR 5// x axis direction control
#define Y_DIR 6// y axis direction control
#define Z_DIR 7// z axis direction control
#define X_STP 2// x axis step control
#define Y_STP 3// y axis step control
#define Z_STP 4// z axis step control

/*
// step(): to control direction and steps of stepper motor
// parameter: dir for direction control, 
//                   dirPin maps to DIR pin of stepper motor,
//                   stepperPin maps to STEP pin of stepper motor
// return value: none
*/

void step(boolean dir, byte dirPin, byte stepperPin, int steps)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(800);
  }
}

void setup (){
  // setup stepper motor I/O pin to output
  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
}

void loop (){
  // 200 steps per turn
  step(false, X_DIR, X_STP, 1800); // run 360 mm
  step(false, Y_DIR, Y_STP, 200); 
  step(false, Z_DIR, Z_STP, 200); 
  delay(1000);
  step(true, X_DIR, X_STP, 1800);  // run 360 mm in reverse direction
  step(true, Y_DIR, Y_STP, 200); 
  step(true, Z_DIR, Z_STP, 200); 
  delay(1000);
}

