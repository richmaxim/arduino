// 
// 
// 

#include "CommandProcessor.h"

void CommandProcessor::init(Stream *stream, char* (*commandHandler)(const char* command), bool echo)
{
	_stream = stream;
    _echo = echo;
    _commandHandler = commandHandler;
}

void CommandProcessor::proceed()
{
	if (readCommand())
	{
		if (_echo) _stream->println(_command);
		if (_commandHandler == NULL)
		{
			_stream->print(ERR);
			_stream->println(NO_HANDLER_ERROR);
		}
		else
		{
			char *status = _commandHandler(_command);
			if (status == NULL || strlen(status) == 0)
			{
				_stream->println(OK);
			}
			else
			{
				_stream->print(ERR);
				_stream->println(status);
			}
		}
		_command[0] = '\0';
	}
}

bool CommandProcessor::readCommand()
{
	size_t idx = strnlen(_command, DEFAULT_COMMAND_LENGTH - 1);
	while (_stream->available())
	{
		if (readEol()) return true;

		if (idx < DEFAULT_COMMAND_LENGTH - 1)
		{
			_command[idx++] = ((char)(_stream->read()));
			_command[idx] = TERMINATOR;
		}
		else
		{
			_stream->read();
		}
	}
}

bool CommandProcessor::readEol()
{
	bool eol = false;
	for (int ch = _stream->peek(); _stream->available() && (ch == CR || ch == LF); ch = _stream->peek())
	{
		_stream->read();
		eol = true;
	}
	return eol;
}
