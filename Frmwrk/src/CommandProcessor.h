// CommandProcessor.h

#ifndef _COMMANDPROCESSOR_h
#define _COMMANDPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define DEFAULT_COMMAND_LENGTH 96

#include "Stream.h"

class CommandProcessor
{
public:
	const char CR = '\r';
	const char LF = '\n';
	const char TERMINATOR = '\0';
	const char *OK = "OK";
	const char *ERR = "ERR: ";
	const char *NO_HANDLER_ERROR = "NO HANDLER";

protected:
	Stream *_stream = NULL;
	char _command[DEFAULT_COMMAND_LENGTH];
	bool _echo = false;
	char* (*_commandHandler)(const char* command);

public:
	void init(Stream *stream, char* (*commandHandler)(const char* command), bool echo);

	void proceed();

	bool readCommand();
	bool readEol();
};

#endif

