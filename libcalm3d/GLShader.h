#ifndef _GLSHADER_H_
#define _GLSHADER_H_

#include "Common.h"

NS_CALM_BEGIN

class GLShader
{
public:
	GLShader(const std::string& file);
	GLShader(const std::string& file, GLenum shader_type);
	~GLShader();

public:
	bool initWithFile(const std::string& file, GLenum shader_type);
	GLuint getShader() { return _shader; }

protected:
	bool load();
	bool checkGLError(GLuint shader);

protected:
	GLuint _shader;
	GLenum _shaderType;
	std::string _file;
};

NS_CALM_END

#endif // _GLSHADER_H_