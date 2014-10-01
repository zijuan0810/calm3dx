#include "GLProgram.h"

using namespace std;

NS_CALM_BEGIN

#define MAX_BUFFER 1024

GLProgram::GLProgram()
{
}

GLProgram::~GLProgram()
{

}

bool GLProgram::init()
{
	_vertShader = 0;
	_fragShader = 0;
	_tcsShader = 0;
	_tesShader = 0;
	_geoShader = 0;
	_program = glCreateProgram();

	return true;
}

void GLProgram::setVertShader(const std::string& file)
{
	GLShader shader(file, GL_VERTEX_SHADER);
	_vertShader = shader.getShader();
	assert(_vertShader > 0);

	glAttachShader(_program, _vertShader);
	link();
}

void GLProgram::setFragShader(const std::string& file)
{
	GLShader shader(file, GL_FRAGMENT_SHADER);
	_fragShader = shader.getShader();
	assert(_fragShader > 0);
	glAttachShader(_program, _fragShader);

	link();
}

GLuint GLProgram::getProgram()
{
	return _program;
}

bool GLProgram::checkError()
{
	GLint logLen = 0;
	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logLen);

	GLint status = 0;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		char buf[MAX_BUFFER] = { 0 };
		glGetProgramInfoLog(_program, MAX_BUFFER, nullptr, buf);
		fprintf(stderr, "%d: %s\n", _program, buf);
		return false;
	}

	return true;
}

void GLProgram::link()
{
	//glLinkProgram(_program);
	//assert(checkError());
	if (_vertShader > 0 && _fragShader > 0) {
		glLinkProgram(_program);
		checkError();
	}
}

void GLProgram::setTcsShader(const std::string& file)
{
	GLShader shader(file, GL_TESS_CONTROL_SHADER);
	_tcsShader = shader.getShader();
	assert(_tcsShader > 0);
	glAttachShader(_program, _tcsShader);

	link();
}

void GLProgram::setTesShader(const std::string& file)
{
	GLShader shader(file, GL_TESS_EVALUATION_SHADER);
	_tesShader = shader.getShader();
	assert(_tesShader > 0);
	glAttachShader(_program, _tesShader);

	link();
}

void GLProgram::setGeoShader(const std::string& file)
{
	GLShader shader(file, GL_GEOMETRY_SHADER);
	_geoShader = shader.getShader();
	assert(_geoShader > 0);
	glAttachShader(_program, _geoShader);

	link();
}

void GLProgram::loadVertShader(const std::string& file)
{
	/*
	FILE* fp = fopen(file.c_str(), "rb");
	if (fp) {
		fseek(fp, 0, SEEK_END);
		size_t filesize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char* buffer = (char*)malloc(filesize);
		filesize = fread(buffer, sizeof(char), filesize, fp);
		fclose(fp);


	}

	FILE* fp = fopen(file.c_str(), "rb");
	fseek(fp, 0, SEEK_END);
	size_t filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* data = new char[filesize + 1];
	fread(data, 1, filesize, fp);
	data[filesize] = 0;
	fclose(fp);

	program = glCreateProgram();
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fs, 1, fs_source, NULL);
	glShaderSource(fs, 1, &data, NULL);
	glCompileShader(fs);
	*/
}

NS_CALM_END