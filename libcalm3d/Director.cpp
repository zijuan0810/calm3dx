#include "Director.h"
#include <assert.h>
#include "GLView.h"
#include <vector>
#include <algorithm>

NS_CALM_BEGIN

Director* Director::sm_instance = nullptr;
Director* Director::Instance()
{
	if (sm_instance == nullptr) {
		sm_instance = new Director();
		if (sm_instance && sm_instance->init()) {
			return sm_instance;
		}
	}

	assert(sm_instance);
	return sm_instance;
}

Director::Director()
	: _glview(nullptr)
{
}

Director::~Director()
{
	CM_SAFE_DELETE(_glview);
}

bool Director::init()
{
	_glview = nullptr;
	return true;
}

void Director::setOpenGLView(GLView* view)
{
	_glview = view;

	_winSizeInPoints = _glview->getFrameSize();
	if (_glview) {
		this->setGLDefaultValues();
	}
}

GLView* Director::getOpenGLView() const
{
	return _glview;
}

bool Director::isExtensionSupported(const char* name)
{
	static std::vector<std::string> vecExtensions;
	if (vecExtensions.size() == 0) {
		GLint num = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &num);
		for (GLuint i = 0; i < num; ++i) {
			const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
			vecExtensions.push_back(extension);
		}
	}

	return std::find(vecExtensions.begin(), vecExtensions.end(), name) != vecExtensions.end();
}

void Director::setGLDefaultValues()
{
	if (_glview) {
		_glview->setViewPortInPoints(0, 0, _winSizeInPoints.width, _winSizeInPoints.height);
	}

	float aspect = float(_winSizeInPoints.width) / float(_winSizeInPoints.height);
	_projectMatrix = vmath::perspective(50.0f, aspect, 0.1f, 1000.0f);
}

NS_CALM_END