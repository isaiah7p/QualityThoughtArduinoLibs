
int x_pin = 0;
int y_pin = 1;
int z_pin = 2; 

int x_led = 6;

int y_led = 7;

int z_led = 8;

int x_out =0 ;
int y_out =0 ;
int z_out =0 ;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
//
//pinMode(x_led,OUTPUT);
//pinMode(y_led,OUTPUT);
//pinMode(z_led,OUTPUT);

Serial.print("in Setup Method ");
}

void loop() {
  Serial.print("in loop Method ");
  // put your main code here, to run repeatedly:
  x_out = analogRead(x_pin);
  analogWrite(x_led,x_out);
  Serial.println(x_out);
  y_out = analogRead(y_pin);
  analogWrite(y_led,y_out);
  Serial.println(y_out);
  z_out = analogRead(z_pin);
  Serial.println(z_out);
  analogWrite(z_led,z_out);
  
}
