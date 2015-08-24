//
//
//

#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(byte sh_cpPin, byte st_cpPin, byte dsPin, bool inverted)
{
  _sh_cpPin = sh_cpPin;
  _st_cpPin = st_cpPin;
  _dsPin = dsPin;
  _inverted = inverted;
}

void ShiftRegister::init()
{
  pinMode(_st_cpPin, OUTPUT);
  pinMode(_sh_cpPin, OUTPUT);
  pinMode(_dsPin, OUTPUT);
}
  
void ShiftRegister::open()
{
  digitalWrite(_st_cpPin, LOW);
}

void ShiftRegister::writeByte(byte state)
{
  for(size_t i=0;i<8;i++)
  {
    writeBit(state & (1 << i));
  }
}

void ShiftRegister::writeBit(bool state)
{
    if(_inverted) state = !state;
    digitalWrite(_dsPin, state ? HIGH : LOW);
    digitalWrite(_sh_cpPin, HIGH);
    digitalWrite(_sh_cpPin, LOW);
}

void ShiftRegister::writeBytes(byte* states, int length)
{
  for(size_t i=0;i<length;i++)
  {
    writeByte(states[i]);
  }
}

void ShiftRegister::close()
{
  digitalWrite(_st_cpPin, HIGH);
}

