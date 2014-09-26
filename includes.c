
#include "includes.h"

void dbg(const char * format, ...)
{
	char message[1024] = { 0 };

	va_list args;
	va_start(args, format);
	wvnsprintfA(message, sizeof(message) - 1, format, args);
	va_end(args);

	OutputDebugStringA(message);
}
