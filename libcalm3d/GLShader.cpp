#include "GLShader.h"
#include <assert.h>
#include <memory>

using namespace std;

NS_CALM_BEGIN

#define MAX_BUFFER 1024

GLShader::GLShader(const std::string& file, GLenum shader_type)
: _shader(0)
{
	initWithFile(file, shader_type);
}

GLShader::GLShader(const std::string& file)
{
}

GLShader::~GLShader()
{
	if (_shader > 0) {
		glDeleteShader(_shader);
	}
}

bool GLShader::initWithFile(const std::string& file, GLenum shader_type)
{
	_file = file;
	_shaderType = shader_type;

	return load();
}

bool GLShader::checkGLError(GLuint shader)
{
	GLint status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		char buf[MAX_BUFFER] = { 0 };
		glGetShaderInfoLog(shader, MAX_BUFFER, nullptr, buf);
		fprintf(stderr, "%s: %s\n", _file.c_str(), buf);
		return true;
	}

	return false;
}

bool GLShader::load()
{
	FILE* fp = fopen(_file.c_str(), "rb");
	if (fp == nullptr) {
		return false;
	}

	fseek(fp, 0, SEEK_END);
	size_t filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* buffer = new char[filesize + 1];
	shared_ptr<char> tmp(buffer);
	fread(buffer, 1, filesize, fp);
	buffer[filesize] = 0;
	fclose(fp);

	_shader = glCreateShader(_shaderType);
	glShaderSource(_shader, sizeof(char), &buffer, nullptr);
	glCompileShader(_shader);

	if (checkGLError(_shader)) {
		return false;
	}

	return true;
}

NS_CALM_END