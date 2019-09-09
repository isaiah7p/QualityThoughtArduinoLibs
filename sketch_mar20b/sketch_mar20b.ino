#include<AFMotor.h>
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

#include <Servo.h>
Servo My_servo;
int trig=11;
int vcc=7;
int gnd=4;
int echo=12;
int pin=2;
float min_val=0;
int i;
float ultra_distance[90]={0};
int angle[91]={0};

void setup() {
  // gear dc motor
motor1.setSpeed(0);
motor2.setSpeed(0);
motor3.setSpeed(0);
motor4.setSpeed(0);
pinMode(pin,OUTPUT);
 My_servo.attach(9,600,2300);
  My_servo.write(600);
 pinMode(trig,OUTPUT);
 pinMode(gnd,OUTPUT);
 pinMode(vcc,OUTPUT);
 pinMode(echo,INPUT);
 digitalWrite(trig,LOW);
 digitalWrite(gnd,LOW);
 digitalWrite(vcc,HIGH);
 digitalWrite(echo,LOW);
 Serial.begin(9600);
}

void loop()
{ digitalWrite(pin,HIGH);
motor1.setSpeed(255);
motor2.setSpeed(255);
motor1.run(FORWARD);
motor2.run(FORWARD);
delay(5000);
motor1.run(RELEASE);
motor2.run(RELEASE);
delay(1000);

  My_servo.write(0);
delay(600);
 int j=0;
 int index=-2;// check index value
  
     for (int i=0; i<=90;i+=1)
          {
          My_servo.write(i);
         delay(50);
         angle[j]=i;
         ultra_distance[j]=measure_distance_cm();
         if (ultra_distance[j]>=50)
{motor1.run(FORWARD);
motor2.run(FORWARD);
//delay(5000);
 }
else
{motor1.run(RELEASE);
motor2.run(RELEASE);        
  
  } 

         delay(20);
         Serial.print(" the iteration = ");
         Serial.print(i);
          Serial.print("  ultra_distance =   ");
         Serial.println(ultra_distance[j]);
         j+=1;   
         if (i==90){break;} 
         }
       for (j=0;j<=90;j+=1)
       {min_val=max(min_val,ultra_distance[j]);
      
        }
         
   for (j=0;j<=90;j+=1)
       {if (min_val>ultra_distance[j])
       {
        min_val=ultra_distance[j];
        index=j;}
       
        }
        
       Serial.print("the min value =");
              Serial.println(min_val);
  Serial.print("the index value =");
              Serial.println(index);
       
        My_servo.write(angle[index]);
        delay(1000);  
     while(true)
        {
          float new_val=0;
        
        new_val= measure_distance_cm();
        Serial.print(" new value  = ");
        Serial.print(new_val);
          if (abs(ultra_distance[index]-new_val)>=2.0)
             {break;
              }}
              
  }     


float measure_distance_cm()
{ float distance =0;
  long time_value=0;
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  time_value=pulseIn(echo,HIGH);
  distance=0.033*time_value/2;
  Serial.print(" distance  = ");
        Serial.print(distance);
  return distance;
  }
