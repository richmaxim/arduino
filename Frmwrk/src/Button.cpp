#include "Button.h"

Button::Button(byte buttonPin, byte defaultState)
{
  _buttonPin = buttonPin;
  _buttonState = _lastButtonState = defaultState;
  _lastDebounceTime = millis();
}

void Button::init(void (*changeHandler)(byte state))
{
  _changeHandler = changeHandler;
  pinMode(_buttonPin, INPUT);
}

void Button::loop()
{
  int buttonState = digitalRead(_buttonPin);
  
  if (buttonState != _lastButtonState) 
  {
    _lastDebounceTime = millis();
  }
  
  if ((millis() - _lastDebounceTime) > DEBOUNCE_DELAY) 
  {
    if (buttonState != _buttonState) 
    {
      _buttonState = buttonState;
      
      if(_changeHandler != NULL) _changeHandler(buttonState);
    }
  }
  _lastButtonState = buttonState;
}
