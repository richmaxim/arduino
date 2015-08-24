#include "Tokenizer.h"
#include "CommandProcessor.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define CMD_OK NULL
CommandProcessor cp;

extern char* commandHandler(const char *command);

const char *PRINT = "PRINT";

void setup() {
  lcd.begin(16, 2);

  Serial.begin(9600);
  cp.init(&Serial, &commandHandler, true);
}

void loop() 
{
  cp.proceed();
}

#define match(t, v) strncasecmp(v, &t.text[t.start], t.len) == 0

char* commandHandler(const char *command)
{
  Tokenizer tz((char*)command, " ");
  Token t = tz.first();

  if (match(t, PRINT))
  {
    t = tz.next(t);
    lcd.clear();
    String text(t.text+t.start);
    lcd.print(text);
    return CMD_OK;
  }
}
