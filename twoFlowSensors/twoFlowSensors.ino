
// CLASS DEFINITION

class FanSpeed {
  
  public:
    void 
      setup(uint8_t irq_pin, void (*ISR_callback)(void), int value),
      handleInterrupt(void);
    double
      getSpeed(),
      getHertz();

  private:
    double
      _timeConstant = 60000000.0;
    uint32_t
      _lastMicros = 0UL,
      _interval = 60000000UL;
    void(*ISR_callback)();
};

void FanSpeed::setup(uint8_t irq_pin, void (*ISR_callback)(void), int value)
{
  attachInterrupt(digitalPinToInterrupt(irq_pin), ISR_callback, value);
}

inline void FanSpeed::handleInterrupt(void)
{
  uint32_t nowMicros = micros();
  _interval = nowMicros - _lastMicros;
  _lastMicros = nowMicros;
}

double FanSpeed::getSpeed()
{
  if (micros() - _lastMicros < 1000000UL) // has rotated in the last second
  {
    return _timeConstant / _interval;
  }
  else
  {
    return 0;
  }   
}

double FanSpeed::getHertz()
{
  if (micros() - _lastMicros < 1000000UL) // has rotated in the last second
  {
    return getSpeed() * 60.0;
  }
  else
  {
    return 0;
  }   
}

// PROGRAM START

FanSpeed* fan1;
uint8_t fan1pin = 2;

FanSpeed* fan2;
uint8_t fan2pin = 3;

void setup()
{
  Serial.begin(9600);
  pinMode(fan1pin, INPUT_PULLUP);
  fan1 = new FanSpeed();
  fan1->setup(fan1pin, []{fan1->handleInterrupt();}, FALLING);
  fan2 = new FanSpeed();
  fan2->setup(fan1pin, []{fan2->handleInterrupt();}, FALLING);
}

void loop()
{
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 1000UL)
  {
    char message[64] = "";
    sprintf(message, "Fan1 Speed:%4d RPM\t%4d Hz", uint32_t(floor(fan1->getSpeed() + 0.5)), uint32_t(floor(fan1->getHertz() + 0.5)));
    sprintf(message, "Fan2 Speed:%4d RPM\t%4d Hz", uint32_t(floor(fan2->getSpeed() + 0.5)), uint32_t(floor(fan2->getHertz() + 0.5)));
    Serial.println(message);
    lastMillis = millis();
  }
}
