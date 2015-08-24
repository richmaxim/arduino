// 
// 
// 

#include "Tokenizer.h"

Tokenizer::Tokenizer(char *text, char *separators)
{
	_text = text;
	_separators = separators;
	_separatorsLength = _separators != NULL ? strlen(_separators) : 0;
}
Token Tokenizer::first()
{
	return next(Token());
}

Token Tokenizer::next(const Token& t)
{
	Token nt;
	nt.text = _text;
	int len = _text != NULL ? strlen(_text) : 0;
	if (len <= 0 || t.start >= len) return nt;
	nt.start = t.start + t.len;
	// Skip separators before token
	while (nt.start < len)
	{
		if (!isSeparator(_text[nt.start])) break;
		nt.start++;
	}
	// Catch token
	while (nt.start + nt.len < len)
	{
		if (isSeparator(_text[nt.start + nt.len])) break;
		nt.len++;
	}
	return nt;
}

bool Tokenizer::isSeparator(char ch)
{
	for (size_t i = 0; i < _separatorsLength; i++)
	{
		if (ch == _separators[i]) return true;
	}
	return false;
}
