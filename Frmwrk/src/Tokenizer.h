// Tokenizer.h

#ifndef _TOKENIZER_h
#define _TOKENIZER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

struct Token
{
public:
	char type = 0;
	int start = 0;
	int len = 0;
	char *text = NULL;

	bool success() { return len > 0; }
};

class Tokenizer
{
 protected:
	 char *_text;
	 char *_separators;
	 int _separatorsLength;

 public:
	 Tokenizer(char *text, char *separators);

	 Token first();
	 Token next(const Token& t);

protected:
	bool isSeparator(char ch);
};

#endif

