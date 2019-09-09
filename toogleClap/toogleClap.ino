
int soundSensor = 2;
int LED = 3;

static boolean toggleButton = false; 

public void changeState(){
  if(toggleButton){
    toggleButton = false;
    }else {

    toggleButton = true;
        
      }
  }

void setup() 
{

  pinMode (soundSensor, INPUT);
  pinMode (LED, OUTPUT);
}

void loop()
{
  int statusSensor = digitalRead (soundSensor);
  
  if (statusSensor == 1)
  {
    changeState();
    digitalWrite(LED, HIGH);
  }
  
  else
  {
    digitalWrite(LED, LOW);
  }
  
}
