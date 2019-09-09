// digital read  & write  --
// analog read   & write 
//
#define pin 2 
#define ledpin 3 
int val = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(pin, INPUT);
  pinMode(ledpin, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:


  val =  digitalRead(pin);
  
  Serial.print(val);

  digitalWrite(ledpin, val);


}
