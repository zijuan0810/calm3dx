#ifndef __SB6_H__
#define __SB6_H__

#ifdef WIN32
    #pragma once
    #define _CRT_SECURE_NO_WARNINGS 1

    #define WIN32_LEAN_AND_MEAN 1
    #include <Windows.h>

	#pragma comment (lib, "glfw.lib")
	#pragma comment (lib, "sb6.lib")
    #pragma comment (lib, "OpenGL32.lib")
#endif

#include "GL/gl3w.h"

#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1
#include "glfw3.h"

#include "sb6ext.h"

#include <stdio.h>
//#include <string.h>
#include <string>
#include <cassert>

namespace sb6
{

class application
{
public:
    application() {}
    virtual ~application() {}

	GLFWwindow* getMainWindow() const { return _mainwnd; }

    virtual void run(sb6::application* the_app)
    {
        bool running = true;
        app = the_app;

        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            return;
        }

        init();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _info.majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _info.minorVersion);

#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif /* _DEBUG */
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_SAMPLES, _info.samples);
        glfwWindowHint(GLFW_STEREO, _info.flags.stereo ? GL_TRUE : GL_FALSE);
        if (_info.flags.fullscreen) {
			int count = 0;
			GLFWmonitor** monitor = glfwGetMonitors(&count);
			assert(count == 1);	// assume only one monitor

			if (_info.wndWidth == 0 || _info.wndHeight == 0) { // make it fullscreen
				const GLFWvidmode* mode = glfwGetVideoMode(monitor[0]);
				_info.wndWidth = mode->width;
				_info.wndHeight = mode->height;
			}

			_mainwnd = glfwCreateWindow(_info.wndWidth, _info.wndHeight, _info.title.c_str(),
				monitor[0], nullptr);
			this->_checkWindow();

			glfwSwapInterval((int)_info.flags.vsync);
        }
        else {
			_mainwnd = glfwCreateWindow(_info.wndHeight, _info.wndHeight, _info.title.c_str(),
				nullptr, nullptr);
			this->_checkWindow();
        }

		// cursor visible
		int value = _info.flags.cursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN;
		glfwSetInputMode(_mainwnd, GLFW_CURSOR, value);

		// window attribute: stereo
		_info.flags.stereo = glfwGetWindowAttrib(_mainwnd, GLFW_STEREO);

		glfwMakeContextCurrent(_mainwnd);

        glfwSetWindowTitle(_mainwnd, _info.title.c_str());
        glfwSetWindowSizeCallback(_mainwnd, glfw_onResize);
        glfwSetKeyCallback(_mainwnd, glfw_onKey);
        glfwSetMouseButtonCallback(_mainwnd, glfw_onMouseButton);
		glfwSetCursorPosCallback(_mainwnd, glfw_onMouseMove);
		glfwSetScrollCallback(_mainwnd, glfw_onMouseWheel);

        gl3wInit();

#ifdef _DEBUG
        fprintf(stderr, "VENDOR: %s\n", (char *)glGetString(GL_VENDOR));
        fprintf(stderr, "VERSION: %s\n", (char *)glGetString(GL_VERSION));
        fprintf(stderr, "RENDERER: %s\n", (char *)glGetString(GL_RENDERER));
#endif

        if (_info.flags.debug)
        {
            if (gl3wIsSupported(4, 3))
            {
                glDebugMessageCallback(debug_callback, this);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            }
            else if (sb6IsExtensionSupported("GL_ARB_debug_output"))
            {
                glDebugMessageCallbackARB(debug_callback, this);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
            }
        }

        startup();

		while (!glfwWindowShouldClose(_mainwnd)) {
			glfwPollEvents();

			render(glfwGetTime());

			glfwSwapBuffers(_mainwnd);
			//glfwSwapInterval();
		}

        shutdown();
        glfwTerminate();
    }

    virtual void init()
    {
		_info.title = "SuperBible6 Example";

        _info.wndWidth = 800;
        _info.wndHeight = 600;
#ifdef __APPLE__
        _info.majorVersion = 3;
        _info.minorVersion = 2;
#else
        _info.majorVersion = 4;
        _info.minorVersion = 3;
#endif
        _info.samples = 0;
        _info.flags.all = 0;
        _info.flags.cursor = 1;
#ifdef _DEBUG
        _info.flags.debug = 1;
#endif
    }

    virtual void startup()
    {

    }

    virtual void render(double currentTime)
    {

    }

    virtual void shutdown()
    {

    }

    virtual void onResize(int w, int h)
    {
        _info.wndWidth = w;
        _info.wndHeight = h;
    }

    virtual void onKey(int key, int action)
    {

    }

    virtual void onMouseButton(int button, int action)
    {

    }

    virtual void onMouseMove(int x, int y)
    {

    }

    virtual void onMouseWheel(int pos)
    {

    }

    virtual void onDebugMessage(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar* message)
    {
#ifdef _WIN32
        OutputDebugStringA(message);
        OutputDebugStringA("\n");
#endif /* _WIN32 */
    }

    static void getMousePosition(double& x, double& y)
    {
		glfwGetCursorPos(app->getMainWindow(), &x, &y);
    }

public:
    struct APPINFO
    {
        int wndWidth;
        int wndHeight;
        int majorVersion;
        int minorVersion;
        int samples;
		std::string title;
        union
        {
            struct
            {
                unsigned int    fullscreen  : 1;
                unsigned int    vsync       : 1;
                unsigned int    cursor      : 1;
                unsigned int    stereo      : 1;
                unsigned int    debug       : 1;
            };
            unsigned int        all;
        } flags;
    };

protected:
	APPINFO		_info;
	GLFWwindow*	_mainwnd;

	static      sb6::application * app;

	static void glfw_onResize(GLFWwindow* wnd, int w, int h)
	{
		app->onResize(w, h);
	}

	static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        app->onKey(key, action);
    }

	static void glfw_onMouseButton(GLFWwindow* wnd, int btn, int action, int mods)
    {
        app->onMouseButton(btn, action);
    }

	static void glfw_onMouseMove(GLFWwindow* wnd, double x, double y)
    {
        app->onMouseMove(x, y);
    }

	static void glfw_onMouseWheel(GLFWwindow* wnd, double x, double y)
    {
        app->onMouseWheel(x);
    }

    void setVsync(bool enable)
    {
        _info.flags.vsync = enable ? 1 : 0;
        glfwSwapInterval((int)_info.flags.vsync);
    }

    static void APIENTRY debug_callback(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei length,
                                        const GLchar* message,
                                        GLvoid* userParam)
    {
        reinterpret_cast<application *>(userParam)->onDebugMessage(source, type, id, severity, length, message);
    }

	private:
		//void _initDeviceConfig();
		int _checkWindow();
		//void _setCallbacks();
		//void _gl3wInit();
};

};

#if defined _WIN32
#define DECLARE_MAIN(a)                             \
sb6::application *app = 0;                          \
int CALLBACK WinMain(HINSTANCE hInstance,           \
                     HINSTANCE hPrevInstance,       \
                     LPSTR lpCmdLine,               \
                     int nCmdShow)                  \
{                                                   \
    a *app = new a;                                 \
    app->run(app);                                  \
    delete app;                                     \
    return 0;                                       \
}
#elif defined _LINUX || defined __APPLE__
#define DECLARE_MAIN(a)                             \
int main(int argc, const char ** argv)              \
{                                                   \
    a *app = new a;                                 \
    app->run(app);                                  \
    delete app;                                     \
    return 0;                                       \
}
#else
#error Undefined platform!
#endif

#endif /* __SB6_H__ */

