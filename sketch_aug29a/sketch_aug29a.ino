//char* myStrings[]={"This is String 1", "This is String 2", "This is String 3",
//"This is String 4", "This is String 5","This is String 6"};

char* myStrings[]={"str1", "str2", "str3"};


void setup(){
Serial.begin(9600);
String stringOne = "Hello String";                                     // using a constant String
 Serial.println(stringOne);
 stringOne =  String('a');                                          // converting a constant char into a String
 Serial.println(stringOne);
 String stringTwo =  String("This is a string");                 // converting a constant string into a String object
 Serial.println(stringTwo);
 stringOne =  String(stringTwo + " with more"); // concatenating two strings
 Serial.println(stringOne);
 stringOne =  String(13);                                          // using a constant integer
 Serial.println(stringOne);
 stringOne =  String(analogRead(0), DEC);          // using an int and a base
 Serial.println(stringOne);
 stringOne =  String(45, HEX);                                // using an int and a base (hexadecimal)
 Serial.println(stringOne);
 stringOne =  String(255, BIN);                               // using an int and a base (binary)
 Serial.println(stringOne);
 stringOne =  String(millis(), DEC);                        // using a long and a base
 Serial.println(stringOne);
 stringOne =  String(5.698, 3); 
 Serial.println(stringOne);

}

void loop(){
for (int i = 0; i < 3; i++){
   Serial.println(myStrings[i]);
   delay(500);
   }
}

