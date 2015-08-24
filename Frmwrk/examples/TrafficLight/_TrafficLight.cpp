#include "TrafficLight.h"

TrafficLight::TrafficLight(byte redPin, byte yellowPin, byte greenPin)
{
  _redPin = redPin;
  _yellowPin = yellowPin;
  _greenPin = greenPin;
  
  _program = NULL;
  _programLength = 0;
  _position = -1;
  _time = 0;
}

void TrafficLight::init()
{
  pinMode(_redPin, OUTPUT);
  pinMode(_yellowPin, OUTPUT);
  pinMode(_greenPin, OUTPUT);
  
  light(OFF);
}

void TrafficLight::light(byte state)
{
  digitalWrite(_redPin, state & RED ? HIGH : LOW);
  digitalWrite(_yellowPin, state & YELLOW ? HIGH : LOW);
  digitalWrite(_greenPin, state & GREEN ? HIGH : LOW);
}

void TrafficLight::loop()
{
  if(_program != NULL)
  {
    bool isNext = false;
    if(_position < 0 || _position >= _programLength)
    {
      _position = 0;
      isNext = true;
    }
    else if(millis() - _time > _program[_position + 1])
    {
      _position += 2; 
      isNext = _position < _programLength;
    }
    
    if(isNext)
    {
      _time = millis();
      light(_program[_position]);
    }
  }
}

void TrafficLight::execute(int *program, int programLength)
{
  light(OFF);
  
  _program = program;
  _programLength = programLength;
  _position = -1;
}
