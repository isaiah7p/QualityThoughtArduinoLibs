#include <SoftwareSerial.h>

int i= 0; 

SoftwareSerial sim800l(10,11); //RX - TX  
//bool res_at(char *buf,char *patern){ 
//  char *ptr;
//
//   ptr = strstr(buf, patern);
//   if (ptr !=0){
//   return true;
//   }else{
//   return false;
//   }
//}
//
//char *debug()
//{
//int i=0;
//char cad[255]="\0";
//char c='\0';
//        
//        strcpy(cad,"");
//        while(sim800l.available()>0)
//        {
//        c=sim800l.read();
//        cad[i]=c;
//        i++;
//        }
//      
//return cad;
//}


void env_sms()
{

Serial.println("SMS block ");
// float flat,flon;
//
//flon = 76.987889;
//flat = 17.897654;
//char charFlat[10] ="";
//char charFlon[10] ="";
//
//ftoa(flat,charFlat,6);
//ftoa(flon,charFlon,6);
//
//
//  char Final_Alert_SMS[100] ;
  
// Final_Alert_SMS = ""+charFlat+","+charFlon;

//strcat(Final_Alert_SMS, "maps.google.com/?q=");
//strcat(Final_Alert_SMS, charFlat);
//strcat(Final_Alert_SMS, ",");
//strcat(Final_Alert_SMS, charFlon);
// Serial.println(Final_Alert_SMS);

 
 sim800l.println(F("AT+CMGF=1"));
 delay(500);
 //if (res_at(debug(),"OK")){
 sim800l.println(F("AT+CMGS=\"+919676867575\""));//
  delay(500); 
 // if(res_at(debug(),">")){
    sim800l.println("Rider Needs at below Location ");
    sim800l.println("maps.google.com/?q=17.471805,78.417425");
    //sim800l.println("maps.google.com");
    delay(500);
    sim800l.println();
    delay(500);
    sim800l.write(0x1A);
    delay(500);
   // }
  //}
Serial.println("SMS Send");

}


void hac_llam(){
   Serial.println("Call ing loop  ");
 sim800l.println(F("ATD+919676867575;"));
 delay(500);
 Serial.println("Call ing loop  ");
//Serial.println(debug());
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
sim800l.begin(9600);

Serial.println("sim800...........");

sim800l.println(F("AT"));
delay(500);
//Serial.println(debug());
sim800l.println(F("AT+CBC"));
delay(500);
Serial.println("Testing");

sim800l.println(F("AT+CSQ"));
delay(500);

//env_sms();
delay(500);
hac_llam();


//char testFlat[10]=""; 
//float tflat = 17.897654;
//
//
//ftoa(tflat,testFlat,7);



//Serial.println("-----------setup finished---------------");
//Serial.print(testFlat);
}

void loop() {

  
float flat = 17.788978;
float flon = 78.234323;

 if(i==0){
 sim800l.println(F("AT+CMGF=1"));
 delay(500);
 //if (res_at(debug(),"OK")){
 sim800l.println(F("AT+CMGS=\"+919676867575\""));//
  delay(500); 
 // if(res_at(debug(),">")){
    sim800l.println("Rider Needs at below Location ");
    sim800l.print("maps.google.com/?q=");
    sim800l.print(flat,6);
     sim800l.print(",");
     sim800l.print(flon,6);

    //sim800l.println("maps.google.com");
    delay(500);
    sim800l.println();
    delay(500);
    sim800l.write(0x1A);
    delay(500);
  // hac_llam();
  // env_sms();
   i++;
 }
}

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
 
 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}
 
// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
 
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
 
    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

