#ifndef _GLVIEW_H_
#define _GLVIEW_H_

#include "Common.h"
#include "Geometry.h"
#include "GLProgram.h"

NS_CALM_BEGIN

/*
 * OpenGL render view
 */
class GLView
{
public:
	GLView();
	GLView(const Size& size);
	virtual ~GLView();

	virtual bool init();

	inline GLFWwindow* getView();
	inline void setView(GLFWwindow* view);

	void setFrameSize(const Size& sz);
	const Size& getFrameSize() { return _frameSize; }

	void setViewPortInPoints(float x, float y, float w, float h);

	void pollEvents();
	void swapBuffers();
	bool windowShouldClose();

	virtual void render(double time) {}
	virtual void onEnter() {}
	virtual void onExit();

	// GLFW callback
	virtual void onGlfwError(int errorID, const char* errorDesc) { std::cout << "dkk" << std::endl; }
	virtual void onGlfwMouse(GLFWwindow* wnd, int button, int action, int modify) {}
	virtual void onGlfwMouseMove(GLFWwindow* wnd, double x, double y) {}
	virtual void onGlfwMouseScroll(GLFWwindow* wnd, double x, double y) {} 
	virtual void onGlfwKey(GLFWwindow* wnd, int key, int scancode, int action, int mods) {}
	virtual void onGlfwChar(GLFWwindow* wnd, unsigned int character) {}
	virtual void onGlfwWindowPos(GLFWwindow* windows, int x, int y) {}
	virtual void onGlfwFramebuffersize(GLFWwindow* wnd, int w, int h) {}
	virtual void onGlfwWindowSize(GLFWwindow *wnd, int width, int height) {}

protected:
	void initGLFW();
	void initGLEW();
	void initGL3W();

protected:
	Size			_frameSize;
	std::string	_viewName;
	GLFWwindow*	_mainwnd;
	GLProgram	_glProgram;
};

NS_CALM_END

#endif // _GLVIEW_H_