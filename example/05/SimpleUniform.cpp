#include "SimpleUniform.h"
#include "Director.h"

using namespace calm3d;


bool SimpleUniform::init()
{
	if (!GLView::init()) {
		return false;
	}

	_glProgram.setVertShader("shaders/05/simpleUniform.vsh.glsl");
	_glProgram.setFragShader("shaders/05/simpleUniform.fsh.glsl");

	glGenBuffers(3, _buf);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// Get all uniform values location
	GLuint program = _glProgram.getProgram();
	GLuint locTime = glGetUniformLocation(program, "fTime");
	GLuint locColorValue = glGetUniformLocation(program, "vColorValue");
	GLuint myUniform = glGetUniformLocation(program, "myUniform");
	log("%d, %d", locTime, locColorValue);

	bool b = Director::Instance()->isExtensionSupported("GL_ARB_explicit_uniform_location");
	glUniform1f(myUniform, 1.0f);
	log("%d, %d", locTime, locColorValue);

	// 获取每个block中变量的偏移量
	const GLchar* uniformNames[4] = {
		"TransformBlok.scale",
		"TransformBlok.translation",
		"TransformBlok.rotation",
		"TransformBlok.projection_matrix",
	};
	GLuint uniformIndices[4] = { 0 };
	glGetUniformIndices(program, 4, uniformNames, uniformIndices);
	
	// 查找uniform block索引
	GLuint blockIndex = glGetUniformBlockIndex(program, "TransformBlock");
	log("TransformBlock idx = %d", blockIndex);

	return true;
}

void SimpleUniform::render(double time)
{
	const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, black);

	static float data_pos[] = {
		0.25, -0.25, 0.0, 1.0,
		-0.25, -0.25, 0.5, 1.0,
		0.25, 0.25, 0.5, 1.0
	};

	glBindBuffer(GL_ARRAY_BUFFER, _buf[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_pos), data_pos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glUseProgram(_glProgram.getProgram());

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}

void SimpleUniform::onEnter()
{
	GLView::onEnter();
}

void SimpleUniform::onExit()
{
	GLView::onExit();
}


//CREATE_MAIN(SimpleUniform);