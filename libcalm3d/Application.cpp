#include "Common.h"
#include "Application.h"
#include "Director.h"
#include "GLView.h"

#include <assert.h>
#include <cstdio>

NS_CALM_BEGIN

Application* Application::sm_instance = nullptr;

Application* Application::Instance()
{
	assert(sm_instance);
	return sm_instance;
}

Application::Application()
{
	sm_instance = this;
}

Application::~Application()
{
	printf("%s", __FUNCTION__);
}

int Application::run()
{
	auto director = Director::Instance();
	auto glview = director->getOpenGLView();
	while (!glview->windowShouldClose()) {
		glview->pollEvents();
		glview->render(glfwGetTime());
		glview->swapBuffers();
	}

	glview->onExit();

	glfwTerminate();
	return 0;
}



NS_CALM_END