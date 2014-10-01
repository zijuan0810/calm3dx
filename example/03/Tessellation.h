#ifndef _TESSELLATION_H_
#define _TESSELLATION_H_

#include "calm3d.h"

class Tessellation : public calm3d::GLView
{
public:
	virtual bool init();
	virtual void render(double time);

	virtual void onExit();

protected:
	GLuint _vao;
};


#endif // _TESSELLATION_H_