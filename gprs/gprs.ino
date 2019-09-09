#include <SoftwareSerial.h>
SoftwareSerial GPRS(10, 11); // RX, TX

  String BUSNUM="A";  // THIS SIM IS TO BE INSTALLED ON BUS A
  static String sendersnumber;
  char* key;
  char MESSAGE[280];
  String latitude;
  String longitude;

  String Speed;

enum _parseState 
{
  PS_DETECT_MSG_TYPE,
  PS_IGNORING_COMMAND_ECHO,

  PS_READ_CMTI_STORAGE_TYPE,
  PS_READ_CMTI_ID,
  PS_DETECT_MSG_TYPE2,
  PS_IGNORING_COMMAND_ECHO2,
  PS_READ_CMGR_STATUS2,
  PS_READ_CMGR_CONTENT2,
  PS_READ_CMGR_DATE2,

  PS_READ_CMGR_STATUS,
  PS_READ_CMGR_NUMBER2,
  PS_READ_CMGR_NUMBER,
  PS_READ_CMGR_SOMETHING,
  PS_READ_CMGR_DATE,
  PS_READ_CMGR_CONTENT,
  PS_READ_VIDEO_CONTENT,
  PS_READ_VIDEO2_CONTENT,
  PS_READ_CMGR_SOMETHING2,
  PS_READ_VIDEO_CONTENT2,
};

byte state = PS_DETECT_MSG_TYPE; // KEEP TRACK OF WHAT STATE WE ARE IN RIGHT NOW

char buffer[100]; // WHAT WE ARE READING INTO

byte pos = 0;  //WHAT POSITION WE ARE AT IN THAT BUFFER

int lastReceivedSMSId = 0;  // LAST RECIEVED SMS ID
boolean validSender = false; //SOO NOT JUST ANYONE HAS ACESS TO SEND A COMMAND


void resetBuffer() 
{
  memset(buffer, 0, sizeof(buffer));
  pos = 0;
}//BASICALLY TO RESET THE BUFFER


void setup()
{

  GPRS.begin(9600);
  Serial.begin(9600);
  GPRS.println("AT+CGNSPWR=1");
  delay(290);
  GPRS.println("AT+CGNSURC=0");
  delay(300);
  GPRS.println("AT");
  delay(300);
  GPRS.println("AT+CMGF=1"); // INITIALIZE SMS
  delay(300);

  for (int i = 1; i <= 15; i++) 
  {
    GPRS.print("AT+CMGD=");
    GPRS.println(i);
    delay(300);
    // Not really necessary but prevents the serial monitor from dropping any input SINCE WE KNOW LIMIT TO STORE IS 15, THIS JUST DELETES IT CLEARS IT
    while(GPRS.available()) 
      Serial.write(GPRS.read());
  }   
    delay(2000);
   GPRS.println("AT+CGNSURC=1");     

}

void loop()
{

 while(GPRS.available()) //ONLY WHEN THERE IS SOMETHING AVAILABLE,
  {


   GSM_NUM1(GPRS.read());  
   //delay(50);
   GPRS.println("AT+CGNSINF");
  // delay(40);    

    GPSAnalyzer(GPRS.read());

    sendSMS();

  }

}
// END OF VOID LOOP



void GSM_NUM1(byte b)
{

  buffer[pos++] = b;

 if ( pos >= sizeof(buffer) )
    resetBuffer(); // just to be safe

 switch (state) 
  {
  case PS_DETECT_MSG_TYPE: 
    {
      if ( b == '\n' )
        resetBuffer();
      else {        
        if ( pos == 3 && strcmp(buffer, "AT+") == 0 ) {
          state = PS_IGNORING_COMMAND_ECHO;
        }
        else if ( pos == 6 ) {
          //Serial.print("Checking message type: ");
          //Serial.println(buffer);

          if ( strcmp(buffer, "+CMTI:") == 0 ) {
            Serial.println("Received CMTI");
            state = PS_READ_CMTI_STORAGE_TYPE;
          }
          else if ( strcmp(buffer, "+CMGR:") == 0 ) {
            Serial.println("Received CMGR");            
            state = PS_READ_CMGR_STATUS;
          }
          resetBuffer();
        }
      }
    }
    break;

  case PS_IGNORING_COMMAND_ECHO:
    {
      if ( b == '\n' ) {
        //Serial.print("Ignoring echo: ");
        //Serial.println(buffer);
        state = PS_DETECT_MSG_TYPE;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMTI_STORAGE_TYPE:
    {
      if ( b == ',' ) {
        Serial.print("SMS storage is ");
        Serial.println(buffer);
        state = PS_READ_CMTI_ID;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMTI_ID:
    {
      if ( b == '\n' ) {
        lastReceivedSMSId = atoi(buffer);
        Serial.print("SMS id is ");
        Serial.println(lastReceivedSMSId);

        GPRS.print("AT+CMGR=");
        GPRS.println(lastReceivedSMSId);
        //delay(500); don't do this!

        state = PS_DETECT_MSG_TYPE;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_STATUS:
    {
      if ( b == ',' ) {
        Serial.print("CMGR status: ");
        Serial.println(buffer);
        state = PS_READ_CMGR_NUMBER;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_NUMBER:
    {
      if ( b == ',' ) {
        Serial.print("CMGR MSSG SENDERS Number: ");
       Serial.println(buffer);
       String sendersnumber=buffer;
        // Uncomment these two lines to check the sender's cell number
        //validSender = false;
        //if ( strcmp(buffer, "\"+0123456789\",") == 0 )
        validSender = true;

        state = PS_READ_CMGR_SOMETHING;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_SOMETHING:
    {
      if ( b == ',' ) {
        Serial.print("CMGR something A.K.A SENDER'S NAME: ");
        Serial.println(buffer);
        state = PS_READ_CMGR_DATE;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_DATE:
    {
      if ( b == '\n' ) {
        Serial.print("CMGR date: ");
        Serial.println(buffer);
        state = PS_READ_CMGR_CONTENT;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_CONTENT:
    {
      if ( b == '\n' ) {
        Serial.print("CMGR MESSAGE Content: ");
        Serial.print(buffer);
         String key=buffer;

       //  sendSMS();
       // GPSAnalyzer();

        GPRS.print("AT+CMGD=");
        GPRS.println(lastReceivedSMSId);

        //delay(500); don't do this!

        state = PS_DETECT_MSG_TYPE;
        resetBuffer();
      }
    }
    break;
  }

}



  void GPSAnalyzer(byte b) 
 {

   buffer[pos++] = b;

  if ( pos >= sizeof(buffer) )
    resetBuffer();// just to be safe

    switch (state) 
  {
  case PS_DETECT_MSG_TYPE2: 
    {
      if ( b == '\n' )
        resetBuffer();
      else {        

        if ( pos == 9 ) {
         // Serial.print("Checking message type: ");
         // Serial.println(buffer);

          if ( strcmp(buffer, "+UGNSINF:") == 0 ) {
            Serial.println("Received CGNSINF:");            
            state = PS_READ_CMGR_STATUS2;
          }
          resetBuffer();
        }
      }
    }
    break;

    //CHECK
    case PS_IGNORING_COMMAND_ECHO2:
    {
      if ( b == '\n' ) {
        //Serial.print("Ignoring echo: ");
        //Serial.println(buffer);
        state = PS_DETECT_MSG_TYPE2;
        resetBuffer();
      }
    }
    break;

//THIS WOULD READ FROM +CGNSINF: (TO THE COMMA),
  case PS_READ_CMGR_STATUS2:
    {
      if ( b == ',' ) {
        Serial.print("RUN STATUS: ");
        Serial.println(buffer);
        String runstatus=buffer;


        state = PS_READ_CMGR_NUMBER2;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_NUMBER2:
    {
      if ( b == ',' ) {
        Serial.print("FIX STATUS : ");
       Serial.println(buffer);

       String fixstatus=buffer;
      fixstatus.replace(","," ");
        validSender = true;

        state = PS_READ_CMGR_SOMETHING2;
        resetBuffer();
      }
    }
    break;
// this is DATE AND TIME i dont need this
  case PS_READ_CMGR_SOMETHING2:
    {
      if ( b == ',' ) {
        Serial.print("DATE AND TIME : ");
        Serial.println(buffer);
        String dateandtime=buffer;

        state = PS_READ_CMGR_DATE2;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_DATE2:
    {
      if ( b == ',' ) {
        Serial.print("LATITUDE: ");
        Serial.println(buffer);
          latitude=buffer;
          latitude.replace(","," ");

        state = PS_READ_CMGR_CONTENT2;
        resetBuffer();
      }
    }
    break;

  case PS_READ_CMGR_CONTENT2:
    {
      if ( b == ',' ) {
        Serial.print("LONGITUDE: ");
        Serial.println(buffer);
        longitude=buffer;
        longitude.replace(","," ");

        state = PS_READ_VIDEO_CONTENT2;
        resetBuffer();
        //delay(500); don't do this!

      }
    }
    break;

   case PS_READ_VIDEO_CONTENT2:
   {
      if ( b == ',' ) {
        Serial.print("ALTITUDE: ");
        Serial.println(buffer);
        String Altitude=buffer;

        state = PS_READ_VIDEO2_CONTENT;
        resetBuffer();
        //delay(500); don't do this!
     }
    }
    break;

    case PS_READ_VIDEO2_CONTENT:
    {
     if ( b == ',' ) {
        Serial.print("SPEED(KM/HR): ");
        Serial.println(buffer);
        String Speed=buffer;
        Speed.replace(","," ");

               state =PS_DETECT_MSG_TYPE2;
        resetBuffer();

      }
    }
    break;
  //use goto to put it at sms begining
  }
 }  

 void sendSMS() 
  {
    if ( strcmp(key,"A") == 0 )
{
 float lati=7.200970;
 float longi=5.181782;
 float Speed1 = atof(Speed.c_str());
 float latituded = atof(latitude.c_str());
 float longituded = atof(longitude.c_str());
 float Distance = HaverSine(lati,longi,latituded,longituded);
 float duration=Distance/Speed1; 
 const int StrLen = 10; 
 char * duration_new ;
 double Value = duration; 
 (void) dtostrf (Value, StrLen, 6, duration_new); 

 String MESSAGE="BUS A";
 MESSAGE+=duration_new ; 
 Serial.print("THE MESSAGE SENT IS ");
 Serial.println(MESSAGE);
}

 else if ( strcmp(key,"B") == 0 )
{
 float lati=7.290970;
 float longi=5.141782;
 float Speed1 = atof(Speed.c_str());
 float latituded = atof(latitude.c_str());
 float longituded = atof(longitude.c_str());
 float Distance = HaverSine(lati,longi,latituded,longituded);
 float duration=Distance/Speed1; 
 const int StrLen = 10; 
 char * duration_new ;
 double Value = duration; 
 (void) dtostrf (Value, StrLen, 6, duration_new); 

 String MESSAGE="BUS B";
 MESSAGE+=duration_new ; 
 Serial.print("THE MESSAGE SENT IS ");
 Serial.println(MESSAGE);
}


  delay(300);
  GPRS.print("AT+CMGF=1\r\n");                                                       
  delay(100);
  GPRS.println("AT+CMGS=\""+sendersnumber+"\"\r\n");                                   
  delay(100);
  GPRS.println(MESSAGE);       
  delay(100);
  GPRS.println((char)26);                       
  delay(100);
  GPRS.println();
  delay(100);
}



float HaverSine(float lat1,float lon1,float lat2,float lon2)
{
  String fixstatus;
 float ToRad = PI / 180.0;
 float R = 6371;   // radius earth in Km

 float dLat = (lat2-lat1) * ToRad;
 float dLon = (lon2-lon1) * ToRad;

 float a = sin(dLat/2) * sin(dLat/2) +
       cos(lat1 * ToRad) * cos(lat2 * ToRad) *
       sin(dLon/2) * sin(dLon/2);
       String o= fixstatus + "8";


 float c = 2 * atan2(sqrt(a), sqrt(1-a));

 float d = R * c;
 return d;
}
