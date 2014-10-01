#include "Log.h"
#include "../Common.h"
#include <cstdarg>

NS_CALM_BEGIN


/// The max length of CCLog message.
static const int MAX_LOG_LENGTH = 16 * 1024;

static void _log(const char* format, va_list args)
{
	char buf[MAX_LOG_LENGTH] = { 0 };

	vsnprintf(buf, MAX_LOG_LENGTH - 3, format, args);
	strcat(buf, "\n");
	/*
	WCHAR wszBuf[MAX_LOG_LENGTH] = { 0 };
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, wszBuf, sizeof(wszBuf));
	OutputDebugStringW(wszBuf);
	WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, buf, sizeof(buf), NULL, FALSE);
	printf("%s", buf);
	fflush(stdout);
	*/

	// Linux, Mac, iOS, etc
	fprintf(stdout, "> %s", buf);
	fflush(stdout);
}

void log(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	_log(format, args);
	va_end(args);
}

NS_CALM_END