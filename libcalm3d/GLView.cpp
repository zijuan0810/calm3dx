#include "GLView.h"
#include <assert.h>

NS_CALM_BEGIN

static void calm3dVersion();

class GLFWEventHandler
{
public:
	static void onGLFWError(int errorID, const char* errorDesc) {
		if (_view) _view->onGlfwError(errorID, errorDesc);
	}

	static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify) {
		if (_view) _view->onGlfwMouse(window, button, action, modify);
	}

	static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y) {
		if (_view) _view->onGlfwMouseMove(window, x, y);
	}

	static void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y) {
		if (_view) _view->onGlfwMouseScroll(window, x, y);
	}

	static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (_view) _view->onGlfwKey(window, key, scancode, action, mods);
	}

	static void onGLFWCharCallback(GLFWwindow* window, unsigned int character) {
		if (_view) _view->onGlfwChar(window, character);
	}

	static void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y) {
		if (_view) _view->onGlfwWindowPos(windows, x, y);
	}

	static void onGLFWframebuffersize(GLFWwindow* window, int w, int h) {
		if (_view) _view->onGlfwFramebuffersize(window, w, h);
	}

	static void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height) {
		if (_view) _view->onGlfwWindowSize(window, width, height);
	}

	static void setGLView(GLView* view) {
		_view = view;
	}

private:
	static GLView* _view;
};

GLView* GLFWEventHandler::_view = nullptr;


//
// GLView
// 
GLView::GLView()
	: GLView(Size(480.0f, 320.0f))
{
}

GLView::GLView(const Size& size)
{
	_viewName = "calm3dx";
	_frameSize = size;

	GLFWEventHandler::setGLView(this);

	glfwSetErrorCallback(GLFWEventHandler::onGLFWError);
	glfwInit();

	//init();
}

GLView::~GLView()
{
	GLFWEventHandler::setGLView(nullptr);
	glfwTerminate();
}

bool GLView::init()
{
	// must be init first !
	initGLFW();
	initGLEW();
	//initGL3W();

	_glProgram.init();

#ifdef _DEBUG
	calm3dVersion();
#endif

	return true;
}

GLFWwindow* GLView::getView()
{
	return _mainwnd;
}

void GLView::setView(GLFWwindow* view)
{
	_mainwnd = view;
}

void GLView::swapBuffers()
{
	if (_mainwnd) {
		glfwSwapBuffers(_mainwnd);
	}
}

bool GLView::windowShouldClose()
{
	if (_mainwnd)
		return glfwWindowShouldClose(_mainwnd) ? true : false;
	else
		return true;
}

void GLView::pollEvents()
{
	glfwPollEvents();
}

void GLView::initGLFW()
{
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	_mainwnd = glfwCreateWindow(_frameSize.width, _frameSize.height, _viewName.c_str(),
		nullptr, nullptr);
	glfwMakeContextCurrent(_mainwnd);

	glfwSetMouseButtonCallback(_mainwnd, GLFWEventHandler::onGLFWMouseCallBack);
	glfwSetCursorPosCallback(_mainwnd, GLFWEventHandler::onGLFWMouseMoveCallBack);
	glfwSetScrollCallback(_mainwnd, GLFWEventHandler::onGLFWMouseScrollCallback);
	glfwSetCharCallback(_mainwnd, GLFWEventHandler::onGLFWCharCallback);
	glfwSetKeyCallback(_mainwnd, GLFWEventHandler::onGLFWKeyCallback);
	glfwSetWindowPosCallback(_mainwnd, GLFWEventHandler::onGLFWWindowPosCallback);
	glfwSetFramebufferSizeCallback(_mainwnd, GLFWEventHandler::onGLFWframebuffersize);
	glfwSetWindowSizeCallback(_mainwnd, GLFWEventHandler::onGLFWWindowSizeFunCallback);
}

void GLView::initGL3W()
{
	/*
	gl3wInit();

#ifdef _DEBUG
	fprintf(stderr, "VENDOR: %s\n", (char *)glGetString(GL_VENDOR));
	fprintf(stderr, "VERSION: %s\n", (char *)glGetString(GL_VERSION));
	fprintf(stderr, "RENDERER: %s\n", (char *)glGetString(GL_RENDERER));
#endif

	if (gl3wIsSupported(4, 3)) {
		//glDebugMessageCallback(debug_callback, this);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}
	*/
}

void GLView::initGLEW()
{
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		assert(0);
	}
}

void GLView::onExit()
{
	glDeleteProgram(_glProgram.getProgram());
}

void GLView::setViewPortInPoints(float x, float y, float w, float h)
{
	glViewport(GLint(x), GLint(y), GLsizei(w), GLsizei(h));
}

void GLView::setFrameSize(const Size& sz)
{
	_frameSize = sz;
	glfwSetWindowSize(_mainwnd, _frameSize.width, _frameSize.height);
}

static void calm3dVersion()
{
	// output header information
	// OpenGL extensions
	printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
	printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	//printf("OpenGL extensions (GL_): %s\n", (const char*)glGetString(GL_EXTENSIONS));

	

#ifndef GLEW_NO_GLU
	/* GLU extensions */
	//printf("GLU version string: %s\n", gluGetString(GLU_VERSION));
	//printf("GLU extensions (GLU_): %s\n", (const char*)gluGetString(GLU_EXTENSIONS));
#endif
}

NS_CALM_END
