#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Common.h"

NS_CALM_BEGIN

/*
 * The Application base
 */
class Application
{
public:
	static Application* Instance();
public:
	Application();
	~Application();

	int run();

protected:
	static Application* sm_instance;
};

NS_CALM_END

#endif // _APPLICATION_H_