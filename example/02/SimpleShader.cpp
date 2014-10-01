#include "SimpleShader.h"

using namespace std;

bool SimpleShader::init()
{
	if (!GLView::init()) {
		return false;
	}

	_glProgram.setVertShader("shaders/02/vsh.glsl");
	_glProgram.setFragShader("shaders/02/fsh.glsl");
	_glProgram.setTcsShader("shaders/02/tcs.glsl");
	_glProgram.setTesShader("shaders/02/tes.glsl");

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return true;
}

void SimpleShader::render(double time)
{
	const GLfloat red[] = {
		(float)cos(time) * 0.5f + 0.5f,
		(float)sin(time) * 0.5f + 0.5f,
		0.0f, 1.0f };
	const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, black);

	glUseProgram(_glProgram.getProgram());

	GLfloat attribPosition[] = { 
		(float)sin(time) * 0.5f,
		(float)cos(time) * 0.6f,
		0.0f, 0.0f
	};
	GLfloat attribColor[] = { 
		(float)sin(time) * 0.5f,
		(float)cos(time) * 0.3f,
		0.0f, 1.0f
	};

	GLfloat attribColor1[] = { 0.0, 0.8, 1.0, 1.0 };

	//glPatchParameteri(GL_PATCH_VERTICES, 3);

	// update the value of input attribute 0
	glVertexAttrib4fv(0, attribPosition);
	glVertexAttrib4fv(1, attribColor1);

	//glDrawArrays(GL_POINTS, 0, 1);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_PATCHES, 0, 3);
}

void SimpleShader::onExit()
{
	glDeleteVertexArrays(1, &_vao);

	GLView::onExit();
}


//CREATE_MAIN(SimpleShader);