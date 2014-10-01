#include "Tessellation.h"

bool Tessellation::init()
{
	if (!GLView::init()) {
		return false;
	}

	_glProgram.setVertShader("shaders/03/vsh.glsl");
	_glProgram.setFragShader("shaders/03/fsh.glsl");
	_glProgram.setTcsShader("shaders/03/tcs.glsl");
	_glProgram.setTesShader("shaders/03/tes.glsl");
	//_program.setGeoShader("shaders/03/geo.glsl");

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return true;
}

void Tessellation::render(double time)
{
	const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, black);

	glPointSize(4);

	glUseProgram(_glProgram.getProgram());
	glDrawArrays(GL_PATCHES, 0, 3);
}

void Tessellation::onExit()
{
	glDeleteVertexArrays(1, &_vao);
	GLView::onExit();
}

//CREATE_MAIN(Tessellation);