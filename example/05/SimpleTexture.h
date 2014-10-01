#ifndef _SIMPLETEXTURE_H_
#define _SIMPLETEXTURE_H_

#include "calm3d.h"

class SimpleTexture : public calm3d::GLView
{
public:
	virtual bool init();
	virtual void render(double time);

protected:
	void generate_texture(float * data, int width, int height);

	virtual void onExit();

	//void drawManyCubes(double time);
	//void drwaOneCube(double time);

	//virtual void onGlfwWindowSize(GLFWwindow *wnd, int width, int height);

protected:
	GLuint	_vao;
	GLuint	_buf[3];
	GLuint	_textureId;

	GLuint	_mvLoc;
	GLuint	_pjLoc;
};

#endif // _SIMPLETEXTURE_H_