#ifndef _SIMPLEUNIFORM_H_
#define _SIMPLEUNIFORM_H_

#include "calm3d.h"

class SimpleUniform : public calm3d::GLView
{
public:
	virtual bool init();
	virtual void render(double time);

	virtual void onEnter();
	virtual void onExit();

protected:
	GLuint	_vao;
	GLuint	_buf[3];
};

#endif // _SIMPLEUNIFORM_H_