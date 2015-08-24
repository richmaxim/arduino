// Button.h

#ifndef _Button_h
#define _Button_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define DEBOUNCE_DELAY 50

class Button
{
private:
  byte _buttonPin;
  byte _buttonState;
  byte _lastButtonState;
  long _lastDebounceTime;
  void (*_changeHandler)(byte state);
public:
  Button(byte buttonPin, byte defaultState);
  
  void init(void (*changeHandler)(byte state));
  
  void loop();
   
};

#endif

