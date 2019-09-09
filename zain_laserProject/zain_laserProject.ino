// Demonstrates the use of Laser obstacle detection.

// The Arduino circuit connection for 7219:
// MAX7219 DIN pin to Arduino digital pin 4
// MAX7219 LOAD pin to Arduino digital pin 3
// MAX7219 CLOCK pin to Arduino digital pin 2

// Laser Module digital output to Arduino digital pin 5


//#define DEBUG_PRINT
//
//#define AA B01110111
//#define BB B00011111
//#define CC B00001101
//#define EE B01101111
//#define FF B01000111
//#define LL B00001110
//#define OO B00011101
//#define RR B00000101
//#define SS B01011011
//#define TT B00001111

//We always have to include the library
//#include "LedControl.h"

unsigned int count = 0x00;
unsigned int count_one = 0x00;
unsigned int previous = 0x00;

//int speakerPin = 8;

int detect_obstacle=5;

//LedControl myDisplay=LedControl(4,2,3,1);

void setup()
{
  pinMode(detect_obstacle,INPUT);
  //pinMode (speakerPin, OUTPUT);

 
//  //The MAX7219 is in power-saving mode on startup, we have to do a wakeup call   
//  myDisplay.shutdown(0,false);
//  //Set the brightness to a medium values
//  myDisplay.setIntensity(0,8);
//  //Clear the display
//  myDisplay.clearDisplay(0); 
//  
//  #ifdef DEBUG_PRINT
    Serial.begin(9600);
    Serial.println("Laser Obstacle detection / counter");
    // 2 Second delay
    delay(100);
 // #endif
  
}
void loop()
{

if(digitalRead(detect_obstacle)==LOW){
     Serial.println("Laser Obstacle detected");
  }else{
     Serial.println("Free");
  }
  
//  if(digitalRead(detect_obstacle)==LOW)
//  {      
//      if(previous == count)
//      {
//         // #ifdef DEBUG_PRINT
//            Serial.println("Obstruct");
//         // #endif
//
////           analogWrite (speakerPin, 255);
////          delay (50);
////           analogWrite (speakerPin, 0);
////          delay (10);
//          
//          count++;
//         
//         //Reset the counter 
//         if(count >= 1000)
//         {
//           count = 0;
//         }
//         
////          myDisplay.clearDisplay(0);
////          //Show the finding on 7 Segment display
////          myDisplay.setRow(0,7,OO);
////          myDisplay.setRow(0,6,BB);
////          myDisplay.setRow(0,5,SS);
////          myDisplay.setRow(0,4,TT);
////          myDisplay.setRow(0,3,AA);
////          myDisplay.setRow(0,2,CC);
////          myDisplay.setRow(0,1,LL);
////          myDisplay.setRow(0,0,EE);  
//
// 
//      }                  
//  }
//  else
//  {
//    if(previous != count)
//    {
//     // #ifdef DEBUG_PRINT
//        Serial.println("Free");
//        //print the counted value
//        Serial.print("Count =");
//        Serial.println(count);
//    //  #endif
////    
////      myDisplay.clearDisplay(0);
////      //Show the finding on 7 Segment display
////      myDisplay.setRow(0,7,FF);
////      myDisplay.setRow(0,6,RR);
////      myDisplay.setRow(0,5,EE);
////      myDisplay.setRow(0,4,EE);   
//            
//      count_one = HexToBCD(count);
////  
////      myDisplay.setDigit(0, 2, ((count_one>>8)&0x0F), false);
////      myDisplay.setDigit(0, 1, ((count_one>>4)&0x0F), false);
////      myDisplay.setDigit(0, 0, (count_one&0x0F), false);
//      previous = count;
//    }    
//  }  
  delay(10);
}

/**************************************************************************/
/*!
 * \brief Coverts hex into BCD
 *
 * This function will coverts hex into BCD
 *
 * \param[in] byte
 * \param[out] byte
 * \return Nill
 * 
 */
/**************************************************************************/
unsigned int HexToBCD(unsigned int number)
{
    unsigned char i=0;
    unsigned int k = 0;

    while(number)
    {
        k = ( k ) | ((number%10) << i*4);
        number = number / 10;
        i++;
    }

    return(k);
}
