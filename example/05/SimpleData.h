#ifndef _SIMPLEDATA_H_
#define _SIMPLEDATA_H_

#include "calm3d.h"

#define MAX_BUFF_NUM 10

class SimpleData : public calm3d::GLView
{
public:
	virtual bool init();
	virtual void render(double time);

	virtual void onEnter();
	virtual void onExit();

protected:
	void render_updateBufferMethod1();
	void render_updateBufferMethod2();
	void render_arrayOfStructure();
	void render_structureOfArray();

protected:
	GLuint _vao;

	GLuint	_buffers[MAX_BUFF_NUM];
};

#endif // _SIMPLEDATA_H_