#include "SpinnyCube.h"
#include "Director.h"

using namespace calm3d;

static const GLfloat vertex_positions[] = {
	-0.25f, 0.25f, -0.25f,
	-0.25f, -0.25f, -0.25f,
	0.25f, -0.25f, -0.25f,

	0.25f, -0.25f, -0.25f,
	0.25f, 0.25f, -0.25f,
	-0.25f, 0.25f, -0.25f,

	0.25f, -0.25f, -0.25f,
	0.25f, -0.25f, 0.25f,
	0.25f, 0.25f, -0.25f,

	0.25f, -0.25f, 0.25f,
	0.25f, 0.25f, 0.25f,
	0.25f, 0.25f, -0.25f,

	0.25f, -0.25f, 0.25f,
	-0.25f, -0.25f, 0.25f,
	0.25f, 0.25f, 0.25f,

	-0.25f, -0.25f, 0.25f,
	-0.25f, 0.25f, 0.25f,
	0.25f, 0.25f, 0.25f,

	-0.25f, -0.25f, 0.25f,
	-0.25f, -0.25f, -0.25f,
	-0.25f, 0.25f, 0.25f,

	-0.25f, -0.25f, -0.25f,
	-0.25f, 0.25f, -0.25f,
	-0.25f, 0.25f, 0.25f,

	-0.25f, -0.25f, 0.25f,
	0.25f, -0.25f, 0.25f,
	0.25f, -0.25f, -0.25f,

	0.25f, -0.25f, -0.25f,
	-0.25f, -0.25f, -0.25f,
	-0.25f, -0.25f, 0.25f,

	-0.25f, 0.25f, -0.25f,
	0.25f, 0.25f, -0.25f,
	0.25f, 0.25f, 0.25f,

	0.25f, 0.25f, 0.25f,
	-0.25f, 0.25f, 0.25f,
	-0.25f, 0.25f, -0.25f
};


bool SpinnyCube::init()
{
	if (!GLView::init()) {
		return false;
	}

	_glProgram.setVertShader("shaders/05/SpinnyCube.vsh.glsl");
	_glProgram.setFragShader("shaders/05/SpinnyCube.fsh.glsl");

	// Get all uniform values location
	GLuint program = _glProgram.getProgram();
	//_mvLoc = glGetUniformLocation(program, "mv_matrix");
	//_pjLoc = glGetUniformLocation(program, "proj_matrix");
	_mvLoc = 10;
	_pjLoc = 11;
	log("%d, %d", _mvLoc, _pjLoc);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// 产生buffer，并绑定数据
	glGenBuffers(3, _buf);
	glBindBuffer(GL_ARRAY_BUFFER, _buf[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
	// 填充顶点属性
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

void SpinnyCube::render(double time)
{
	static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;

	//glViewport(0, 0, info.windowWidth, info.windowHeight);
	//glViewport(0, 0, _frameSize.width, _frameSize.height);
	glClearBufferfv(GL_COLOR, 0, green);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(_glProgram.getProgram());

	glUniformMatrix4fv(_pjLoc, 1, GL_FALSE, mProjectMatrix);

	this->drwaOneCube(time);
	this->drawManyCubes(time);
}

void SpinnyCube::drawManyCubes(double time)
{
	for (int i = 0; i < 24; ++i) {
		float f = (float)i + (float)time * 0.3f;
		zmath::mat4 mv_matrix = zmath::translate(0.0f, 0.0f, -6.0f) *
			zmath::rotate((float)time * 45.0f, 0.0f, 1.0f, 0.0f) *
			zmath::rotate((float)time * 21.0f, 1.0f, 0.0f, 0.0f) *
			zmath::translate(sinf(2.1f * f) * 2.0f, cosf(1.7f * f) * 2.0f, sinf(1.3f * f) * cosf(1.5f * f) * 2.0f);
		glUniformMatrix4fv(_mvLoc, 1, GL_FALSE, mv_matrix);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void SpinnyCube::onGlfwWindowSize(GLFWwindow *wnd, int width, int height)
{
	GLView::onGlfwWindowSize(wnd, width, height);
	float aspect = float(width) / float(height);
	mProjectMatrix = zmath::perspective(50.0f, aspect, 0.1f, 1000.0f);
}

void SpinnyCube::drwaOneCube(double time)
{
	float f = (float)time * 0.3f;
	zmath::mat4 mv_matrix = zmath::translate(0.0f, 0.0f, -4.0f) *
		zmath::translate(sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f, sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) *
		zmath::rotate((float)time * 45.0f, 0.0f, 1.0f, 0.0f) *
		zmath::rotate((float)time * 81.0f, 1.0f, 0.0f, 0.0f);
	glUniformMatrix4fv(_mvLoc, 1, GL_FALSE, mv_matrix);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


//CREATE_MAIN(SpinnyCube);