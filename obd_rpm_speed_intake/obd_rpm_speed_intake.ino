////// code WORKING BUT NOT OPTIMIZED!!!
///// i modified MediumNumbers -> add space simbol instead "/" 

//Подключаем блютус, заранее соединенный с адартером, на RX TX - на serial порт ардуино

#include <Arduino.h>
#include <Wire.h>
#include <OBD.h>
#include <LCD5110_Graph.h>

//************************************подключаем дисплей
#define   SCK   4
#define   MOSI  5
#define   DC   6
#define   RST  8
#define   CS   7

LCD5110 myGLCD( SCK , MOSI , DC , RST , CS );
extern uint8_t SmallFont[]; // массивов символов
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

const int backlight = 2; //пин управления подсветкой
//******************************************************

//************************************настраиваем кнопку
const int buttonPin = 9; 
int menuPage=0;
//************************************

const int ledPin =  13; 
int Gear;
int type;

COBD obd;

int temp, tempOld;
boolean start=true;
int state;
boolean newPage;

void setup()
{
  Serial.begin(9600);
  myGLCD.InitLCD(); // Инициализация дисплея
  pinMode(backlight, OUTPUT); //инициализируем пин подсветки
  
  pinMode(buttonPin, INPUT); //инициализируем пин кнопки

  digitalWrite(backlight, LOW);
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr(); 
  myGLCD.print("hello", CENTER,8 );
  myGLCD.print("pls wait, i'm", CENTER,16 );
  myGLCD.print("connecting", CENTER, 24);
  myGLCD.print("to your MINI", CENTER, 32);
  myGLCD.update();
  delay(3000);     
  // start communication with OBD-II UART adapter
  obd.begin();
  // initiate OBD-II connection until success
  while (!obd.init());
  
  myGLCD.clrScr();  
  myGLCD.print("have a nice", CENTER, 16);
  myGLCD.print("trip", CENTER, 24);
  myGLCD.update();
  delay(2000);
  myGLCD.print(";)", CENTER, 32);
  myGLCD.update();
  delay(2000);
  myGLCD.clrScr();  
}

void loop()
{
        
   
  
  if (newPage) myGLCD.clrScr();      
  if (menuPage>0) type = 1;
  
  switch (menuPage) {
    case 0:
      type=0;
      print_coolant_temp();
      print_intake_pressue();
      print_engine_load();
      break;
    case 1:
      print_coolant_temp();
      break;
    case 2:
      print_intake_pressue();
      break;
    case 3:
      print_engine_load();
      break;   
    case 4:
      print_speed(0);
      break; 
    case 5:
      print_speed(1);
      break;
    case 6:
      print_speed(2);
      break; 
    case 7:
      print_gear();
      break; 
  }
  
  if (newPage) delay(400); 
  state = digitalRead(buttonPin) == HIGH ? 1 : 0;
  newPage = state == 1 ? true : false;
  if (state == 1) menuPage += state;
  if (menuPage > 7) menuPage=0;
    

}

void print_coolant_temp() {


  
  if (obd.read(PID_COOLANT_TEMP, temp)) {


    switch (type) {
      case 0:    
       myGLCD.setFont(SmallFont);
        if (tempOld < temp) 
          myGLCD.print("  >>>", 0, 0);
        if (tempOld > temp)
          myGLCD.print("  <<<", 0, 0);
        if (tempOld != temp)  tempOld = temp;
       
        myGLCD.print("Temp C", 6, 8);
        myGLCD.setFont(MediumNumbers);
        myGLCD.printNumI(temp, RIGHT, 0, 3, '/');
        myGLCD.update(); 
        break;
      case 1:
       myGLCD.setFont(SmallFont);
       myGLCD.print(" ", 2, 0);
       myGLCD.print("t", 2, 8);
       myGLCD.print("e", 2, 16);
       myGLCD.print("m", 2, 24);
       myGLCD.print("p", 2, 32);
       myGLCD.print(" ", 2, 40);
       
       if (tempOld < temp) 
          myGLCD.print("  >>>", CENTER, 40);
        if (tempOld > temp)
          myGLCD.print("  <<<", CENTER, 40);
        if (tempOld != temp)  tempOld = temp;
        
       
       myGLCD.setFont(BigNumbers);
       myGLCD.printNumI(temp, CENTER,8 );
       myGLCD.update();
       break; 
    }
  }
  
  
}

void print_intake_pressue() {
int pressue;
      

  
  if (obd.read(PID_INTAKE_MAP, pressue)) {
   
    switch (type) {
      case 0:    
          myGLCD.setFont(SmallFont);
          myGLCD.print("Intake", 6, 24);
          myGLCD.setFont(MediumNumbers);
          myGLCD.printNumI(pressue, RIGHT, 16, 3, '/');
          myGLCD.update();
        break;
      
      case 1:
       myGLCD.setFont(SmallFont);
       myGLCD.print("i", 2, 0);
       myGLCD.print("n", 2, 8);
       myGLCD.print("t", 2, 16);
       myGLCD.print("a", 2, 24);
       myGLCD.print("k", 2, 32);
       myGLCD.print("e", 2, 40);
       
       myGLCD.setFont(BigNumbers);
       myGLCD.printNumI(pressue, CENTER,8, 3, '/');
       myGLCD.update();
       break; 
    }
  }
  
}

void print_engine_load() {
int engineLoad;
  
  if (obd.read(PID_ENGINE_LOAD, engineLoad)) {

    switch (type) {
      case 0:    
          myGLCD.setFont(SmallFont);
          myGLCD.print("Load %", 6, 40);
          myGLCD.setFont(MediumNumbers);
          myGLCD.printNumI(engineLoad, RIGHT, 32, 3, '/');
          myGLCD.update();
        break;
      
      case 1:
       myGLCD.setFont(SmallFont);
       myGLCD.print(" ", 2, 0);
       myGLCD.print("l", 2, 8);
       myGLCD.print("o", 2, 16);
       myGLCD.print("a", 2, 24);
       myGLCD.print("d", 2, 32);
       myGLCD.print(" ", 2, 40);
       
       myGLCD.setFont(BigNumbers);
       myGLCD.printNumI(engineLoad, CENTER, 8, 3, '/');
       myGLCD.update();
       break; 
    }
  }
  
}

void print_speed(int t) {
int CarSpeed, rpm;
  
  if (obd.read(PID_SPEED, CarSpeed)) {

       myGLCD.setFont(SmallFont);
       myGLCD.print("S", 2, 0);
       myGLCD.print("P", 2, 8);
       myGLCD.print("E", 2, 16);
       myGLCD.print("E", 2, 24);
       myGLCD.print("D", 2, 32);
      if (t==0) myGLCD.print("*", 2, 40); //просто скорость
      if (t==1) myGLCD.print(">", 2, 40); //индикация повышенных
      if (t==2) myGLCD.print("<*>", 0, 40); //индикация пониженных и повышенных
       
       myGLCD.setFont(BigNumbers);
       myGLCD.printNumI(CarSpeed, CENTER, 8, 3, '/');
       myGLCD.update();
         
  }
 
 if (t !=0) {
     if (obd.read(PID_RPM, rpm)) {
     
                if ((rpm > 5500) and (t==1))  {
                  for (uint8_t i=0; i < 3; i++) {
                     digitalWrite(backlight, HIGH);
                     delay(100);
                     digitalWrite(backlight, LOW);
                     delay(100);
                  }
                }
      
                //вариант сигнализации о низких оборотах
                if ((CarSpeed > 30) and (rpm < 3000) and (t==2)){
                  for (uint8_t i=0; i < 2; i++) {
                     digitalWrite(backlight, HIGH);
                     delay(100);
                     digitalWrite(backlight, LOW);
                     delay(100);
                  }
                }
                
                
     }
 }
 
 
}

void print_gear() {
 int CarSpeed, rpm;
          if (obd.read(PID_RPM, rpm)) {
            if (obd.read(PID_SPEED, CarSpeed)) {
                  get_gear(CarSpeed, rpm);
                   myGLCD.clrScr();
                   myGLCD.setFont(SmallFont);
                   myGLCD.print(" ", 2, 0);
                   myGLCD.print("G", 2, 8);
                   myGLCD.print("E", 2, 16);
                   myGLCD.print("A", 2, 24);
                   myGLCD.print("R", 2, 32);
                   myGLCD.print(" ", 2, 40);
                   
                   myGLCD.setFont(BigNumbers);
                   myGLCD.printNumI(Gear, CENTER, 8);
                   myGLCD.update();
            }
          }   
}


void get_gear(int CarSpeed, int Rpm) {

 float  G1, G2, G3, G4, G5, G6, FinalG, Pi, Ratio, Dia, Diff;
    Dia = 616;
    
    Pi = 3.14;
    
    G1 = 3.308;
    G2 = 2.13;
    G3 = 1.483;
    G4 = 1.139;
    G5 = 0.949;
    G6 = 0.816;
    
    FinalG = 3.706;
 if (CarSpeed != 0) {

     Ratio = (Rpm*Pi*Dia*60)/(CarSpeed*FinalG*1000000);
     Gear = 7;
     
     if ( (-0.1 < Ratio-G1) and  (Ratio-G1 < 0.1) ) Gear = 1;
     if ( (-0.1 < Ratio-G2) and  (Ratio-G2 < 0.1) ) Gear = 2;
     if ( (-0.1 < Ratio-G3) and  (Ratio-G3 < 0.1) ) Gear = 3;
     if ( (-0.1 < Ratio-G4) and  (Ratio-G4 < 0.1) ) Gear = 4;
     if ( (-0.1 < Ratio-G5) and  (Ratio-G5 < 0.1) ) Gear = 5;
     if ( (-0.1 < Ratio-G6) and  (Ratio-G6 < 0.1) ) Gear = 6;
 }
 else Gear = 0 ;
 
  
}
