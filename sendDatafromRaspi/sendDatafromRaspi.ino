const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);  //Open Serial connection at baud 9600
  Serial1.begin(9600);
}

void loop() {
  if (Serial.available()) {
    sendSMS();

    light(Serial.read() == '0');
  }
  delay(500);
}

void light(int n) {

  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}

void sendSMS(){
     Serial1.begin(9600);
    Serial.println("-- SUBBU -- Phone ");

    Serial1.println(F("AT"));
    delay(200);
    //Serial.println(debug());
    Serial1.println(F("AT+CBC"));
    delay(200);
    //Serial.println(debug());
    Serial.println("-- debug  1");
    Serial1.println(F("AT+CSQ"));
    delay(200);
    Serial.println("-- debug  2");
    Serial1.println(F("AT+CMGF=1"));
    delay(200);
    //if (res_at(debug(),"OK")){
    Serial1.println(F("AT+CMGS=\"+919676867575\""));
    Serial.println("-- debug  3");
    delay(200);
    // if(res_at(debug(),">")){
    Serial1.println("Emergency Help for Subash DD ,pls reach him  ");
    Serial.println("-- debug  4");
    Serial1.println("maps.google.com");
    delay(200);
    Serial1.println("");
    delay(200);
    Serial1.write(0x1A);
    delay(200);
    Serial.println("-- sms done ");
  }
