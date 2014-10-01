#ifndef _SPINNYCUBE_H_
#define _SPINNYCUBE_H_

#include "calm3d.h"

class SpinnyCube : public calm3d::GLView
{
public:
	virtual bool init();
	virtual void render(double time);

protected:
	void drawManyCubes(double time);
	void drwaOneCube(double time);

	virtual void onGlfwWindowSize(GLFWwindow *wnd, int width, int height);

protected:
	GLuint	_vao;
	GLuint	_buf[3];

	GLuint	_mvLoc;
	GLuint	_pjLoc;

	zmath::mat4	mProjectMatrix;
};

#endif // _SPINNYCUBE_H_