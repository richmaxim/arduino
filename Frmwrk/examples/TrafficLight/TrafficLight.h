// TrafficLight.h

#ifndef _TrafficLight_h
#define _TrafficLight_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define OFF    0
#define RED    1
#define YELLOW 2
#define GREEN  4


class TrafficLight
{
private:
  byte _redPin;
  byte _yellowPin;
  byte _greenPin;
  
  int *_program;
  int _programLength;
  int _position;
  long _time;
public:
  TrafficLight(byte redPin, byte yellowPin, byte greenPin);
  
  void init();
  void light(byte state);
  
  void loop();
  void execute(int *program, int programLength);
};

#endif

