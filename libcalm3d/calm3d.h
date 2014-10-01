#ifndef _CALM3D_H_
#define _CALM3D_H_

#include "CMMacro.h"
#include "c3dmath.h"

#include "Common.h"
#include "Director.h"
#include "Geometry.h"
#include "GLShader.h"
#include "GLProgram.h"
#include "GLView.h"
#include "Application.h"

#include "base/Log.h"
#include "base/FileUtils.h"

NS_CALM_BEGIN


NS_CALM_END

#ifdef WIN32
	#pragma once
	#define _CRT_SECURE_NO_WARNINGS 1

	#define WIN32_LEAN_AND_MEAN 1
	#include <Windows.h>

	//#pragma comment(lib, "glu32")
	#pragma comment (lib, "glfw.lib")
	#pragma comment (lib, "glew32d.lib")
	#pragma comment (lib, "OpenGL32.lib")
	#pragma comment (lib, "libcalm3d.lib")
#endif

#define CREATE_MAIN(_Class) \
	int main(int argc, const char ** argv)  { \
		using namespace calm3d; \
		AllocConsole(); \
		freopen("CONIN$", "r", stdin); \
		freopen("CONOUT$", "w", stdout); \
		freopen("CONOUT$", "w", stderr); \
		auto director = Director::Instance(); \
		auto glview = director->getOpenGLView(); \
		if (!glview) { \
			glview = new _Class(); \
			glview->init(); \
			glview->setFrameSize(Size(640, 480)); \
			director->setOpenGLView(glview); \
		} \
		Application app; \
		auto ret = Application::Instance()->run(); \
		FreeConsole(); \
		return ret; \
	}

#endif // _CALM3D_H_