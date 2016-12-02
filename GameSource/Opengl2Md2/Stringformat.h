#include <string>
#include <stdarg.h>


std::string format_arg_list(const char *fmt, va_list args)
{
	if (!fmt) return "";
	int   result = -1, length = 1024;
	char *buffer = 0;
	while (result == -1)    {
		if (buffer)
			delete [] buffer;
		buffer = new char [length + 1];
		memset(buffer, 0, length + 1);

		// remove deprecate warning
		//result = _vsnprintf(buffer, length, fmt, args);

		result = _vsnprintf_s(buffer, length, _TRUNCATE, fmt, args);
		length *= 2;
	}
	std::string s(buffer);
	delete [] buffer;
	return s;
}

std::string format(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	std::string s = format_arg_list(fmt, args);
	va_end(args);
	return s;
}