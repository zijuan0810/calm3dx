#ifndef _APPLICATIONINFO_H_
#define _APPLICATIONINFO_H_

#include "Common.h"

NS_CALM_BEGIN

struct APPINFO
{
	int wndWidth;
	int wndHeight;
	int majorVersion;
	int minorVersion;
	int samples;
	std::string title;

	union {
		struct {
			unsigned int fullscreen : 1;
			unsigned int vsync : 1;
			unsigned int cursor : 1;
			unsigned int stereo : 1;
			unsigned int debug : 1;
		};
		unsigned int all;
	} flags;
};

NS_CALM_END

#endif // _APPLICATIONINFO_H_