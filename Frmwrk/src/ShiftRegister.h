// ShiftRegister.h

#ifndef _SHIFTREGISTER_h
#define _SHIFTREGISTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ShiftRegister
{
private:
  byte _sh_cpPin;
  byte _st_cpPin;
  byte _dsPin;
  bool _inverted;

public:
  ShiftRegister(byte sh_cpPin, byte st_cpPin, byte dsPin, bool inverted);
  
  void init();
  
  void open();
  
  void writeByte(byte state);
  void writeBit(bool state);
  void writeBytes(byte* states, int length);
  
  void close();
};

#endif

