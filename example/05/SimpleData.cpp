#include "SimpleData.h"

bool SimpleData::init()
{
	if (!GLView::init()) {
		return false;
	}

	_glProgram.setVertShader("shaders/05/vsh.glsl");
	_glProgram.setFragShader("shaders/05/fsh.glsl");

	// Generate a name for the buffer
	glGenBuffers(MAX_BUFF_NUM, _buffers);
	// Now bind it to the context using the GL_ARRAY_BUFFER binding point
	//glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
	// Specify the amount of storage we want to use for the buffer
	//glBufferData(GL_ARRAY_BUFFER, 1024 * 1024, nullptr, GL_STATIC_DRAW);

	// Generate our attribute array
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	return true;
}

void SimpleData::render(double time)
{
	const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, black);

	//render_updateBufferMethod1();
	//render_updateBufferMethod2();
	//render_arrayOfStructure();
	render_structureOfArray();
}

void SimpleData::onEnter()
{
	GLView::onEnter();
}

void SimpleData::onExit()
{
	glDeleteVertexArrays(1, &_vao);
	GLView::onExit();
}

void SimpleData::render_updateBufferMethod1()
{
	// 数据源
	// This is the data that we will place into the buffer object
	static float data_pos[] = {
		0.25, -0.25, 0.0, 1.0,
		-0.25, -0.25, 0.5, 1.0,
		0.25, 0.25, 0.5, 1.0
	};

	// Now bind it to the context using the GL_ARRAY_BUFFER binding point
	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
	// Specify the amount of storage we want to use for the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_pos), nullptr, GL_STATIC_DRAW);

	// 更新buffer内容
	// Put the data into the buffer at offset 0
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data_pos), data_pos);

	// First, bind our buffer object to the GL_ARRAY_BUFFER binding
	// The subsequent call to glVertexAttributePointer will refrence this buffer
	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);

	// 更新vertex属性
	// Now, describe the data to OpenGL, tell it where it is, and turn on
	// automatic vertex fething for the specified attribute
	glVertexAttribPointer(
		0,			// Attribute location 0
		4,			// Four components
		GL_FLOAT,	// Floating-point type data
		GL_FALSE,	// Not normalized (floating-point data never is)
		0,			// Stride, tightly packed
		nullptr);	// Offset zero (nullptr pointer)
	glEnableVertexAttribArray(0);

	glUseProgram(_glProgram.getProgram());

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}

void SimpleData::render_updateBufferMethod2()
{
	// 数据源
	// This is the data that we will place into the buffer object
	static float data_pos[] = {
		0.25, -0.25, 0.0, 1.0,
		-0.25, -0.25, 0.5, 1.0,
		0.25, 0.25, 0.5, 1.0
	};

	// Now bind it to the context using the GL_ARRAY_BUFFER binding point
	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
	// Specify the amount of storage we want to use for the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_pos), nullptr, GL_STATIC_DRAW);

	// 更新buffer内容 - 方法2
	// Get the pointer to the buffer's data store
	void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	// Copy our data in it...
	memcpy(ptr, data_pos, sizeof(data_pos));
	// Tell OpenGL that we're done with the pointer
	glUnmapBuffer(GL_ARRAY_BUFFER);

	// First, bind our buffer object to the GL_ARRAY_BUFFER binding
	// The subsequent call to glVertexAttributePointer will refrence this buffer
	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);

	// 更新vertex属性
	// Now, describe the data to OpenGL, tell it where it is, and turn on
	// automatic vertex fething for the specified attribute
	glVertexAttribPointer(
		0,			// Attribute location 0
		4,			// Four components
		GL_FLOAT,	// Floating-point type data
		GL_FALSE,	// Not normalized (floating-point data never is)
		0,			// Stride, tightly packed
		nullptr);	// Offset zero (nullptr pointer)
	glEnableVertexAttribArray(0);

	glUseProgram(_glProgram.getProgram());

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}

/*
* 数组结构，即单独多个数组
*/
void SimpleData::render_arrayOfStructure()
{
	// This is the data that we will place into the buffer object
	static float data_pos[] = {
		0.25, -0.25, 0.0, 1.0,
		-0.25, -0.25, 0.5, 1.0,
		0.25, 0.25, 0.5, 1.0
	};

	static float data_clr[] = {
		1.0, 0.0, 0.0, 1.0f,
		0.0, 1.0, 0.0, 1.0f,
		0.0, 0.0, 1.0, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_pos), data_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, _buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data_clr), data_clr, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(1);

	glUseProgram(_glProgram.getProgram());

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}

/*
* 结构数组，即将所有的属性值放在一个数组中，通过glVertexAttribPointer的stride参数
* 来控制
*/
void SimpleData::render_structureOfArray()
{
	struct vertex {
		// Position
		float x;
		float y;
		float z;
		float w;
		// Color
		float r;
		float g;
		float b;
		float a;
	};

	static const vertex vertices[] = {
		{ 0.25, -0.25, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0f },
		{ -0.25, -0.25, 0.5, 1.0, 0.0, 1.0, 0.0, 1.0f },
		{ 0.25, 0.25, 0.5, 1.0, 0.0, 0.0, 1.0, 1.0f },
	};

	glBindBuffer(GL_ARRAY_BUFFER, _buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Set up vertex position attribute
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, x));
	glEnableVertexAttribArray(0);

	// Set up vertex color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, r));
	glEnableVertexAttribArray(1);

	glUseProgram(_glProgram.getProgram());

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}



//CREATE_MAIN(SimpleData);