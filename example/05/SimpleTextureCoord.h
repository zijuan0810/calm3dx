#ifndef _SIMPLETEXTURECOORD_H_
#define _SIMPLETEXTURECOORD_H_

#include "calm3d.h"
#include <memory>
#include "Object3D.h"

class SimpleTextureCoord : public calm3d::GLView
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
	GLuint	_textureIds[2];
	GLuint	mTexIdx;

	GLuint	_mvLoc;
	GLuint	_pjLoc;

	shared_ptr<Object3D> _object;

private:
	struct  {
		GLint mv_matrix;
		GLint proj_matrix;
	} uniforms;
};

#endif // _SIMPLETEXTURECOORD_H_