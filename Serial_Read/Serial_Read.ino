int incomingByte = 0;   // for incoming serial data

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
                 Serial.println("Enter your Age :");
}

void loop() {

        // send data only when you receive data:

        // Serial.flush();
         delay(200);
        if (Serial.available() > 0) {
                // read the incoming byte:
              //  incomingByte = Serial.read();
             
              int age = Serial.read();
              Serial.println(age);
              Serial.println("SEX : ");
              char sex = Serial.read();
              Serial.println(sex);
              
                       //Serial.write(age);
                      // Serial.write(sex);
//                // say what you got:
//                Serial.print("I received: ");
//                Serial.println(incomingByte, DEC);
//                  Serial.println(incomingByte);
        }
}
 
