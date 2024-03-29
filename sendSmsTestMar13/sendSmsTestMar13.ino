/* this library is writing by  Cristian Steib.
 *      steibkhriz@gmail.com
 *  Designed to work with the GSM Sim800l,maybe work with SIM900L
 *  
 *     This library use SoftwareSerial, you can define de RX and TX pin
 *     in the header "Sim800l.h" ,by default the pin is RX=10 TX=11..
 *     be sure that gnd is attached to arduino too. 
 *     You can also change the other preferred RESET_PIN
 *    
 *     Esta libreria usa SoftwareSerial, se pueden cambiar los pines de RX y TX
 *     en el archivo header, "Sim800l.h", por defecto los pines vienen configurado en
 *     RX=10 TX=11.  
 *     Tambien se puede cambiar el RESET_PIN por otro que prefiera
 *     
 *    PINOUT: 
 *        _____________________________
 *       |  ARDUINO UNO >>>   SIM800L  |
 *        -----------------------------
 *            GND      >>>   GND
 *        RX  10       >>>   TX    
 *        TX  11       >>>   RX
 *       RESET 2       >>>   RST 
 *                 
 *   POWER SOURCE 4.2V >>> VCC
 *
 *    Created on: April 20, 2016
 *        Author: Cristian Steib
 *        
 *
*/

#include <Sim800l.h>
#include <SoftwareSerial.h> //is necesary for the library!! 
Sim800l Sim800l;  //to declare the library
char* text;
char* number;
bool error; //to catch the response of sendSms
String dateNetTel;
int i =0 ;
char* buf[10] ;
void setup(){
  Serial.begin(9600);
	Sim800l.begin(); // initializate the library. 
	text=" Hello Joel , Gloria here  ";  //text for the message. 
	number="+919676867575"; //change to a valid number.
  Serial.print("Sending SMS with message :: ");
  Serial.print(text);
  // Sim800l.callNumber(number);
	error=Sim800l.sendSms(number,text);
//  error=Sim800l.sendSms(number,dateNetTel.toCharArray(buf, 10));
	// OR 
	//Sim800l.sendSms("+540111111111","the text go here")
  Serial.print("Error:;");
  


}

void loop(){
	//do nothing
  if(i==0){
  //Serial.print("Loop Started ");
  }else i++;
}
