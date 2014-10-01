#ifndef _SIMPLESHADER_H_
#define _SIMPLESHADER_H_

#include "calm3d.h"

class SimpleShader : public calm3d::GLView
{
public:
	virtual bool init();
	virtual void render(double time);

	virtual void onExit();

protected:
	GLuint _vao;
	
};

#endif // _SIMPLESHADER_H_