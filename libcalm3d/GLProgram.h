#ifndef _GLPROGRAM_H_
#define _GLPROGRAM_H_

#include "Common.h"
#include "GLShader.h"

NS_CALM_BEGIN

class GLProgram
{
public:
	enum {
		VERTEX_ATTRIB_POSITION = 0,
		VERTEX_ATTRIB_COLOR,
		VERTEX_ATTRIB_TEX_COORDS,

		VERTEX_ATTRIB_MAX,
	};

public:
	GLProgram();
	~GLProgram();

	virtual bool init();

	void setVertShader(const std::string& file);
	void setFragShader(const std::string& file);
	void setTcsShader(const std::string& file);
	void setTesShader(const std::string& file);
	void setGeoShader(const std::string& file);

	void loadVertShader(const std::string& file);

	void link();
	GLuint getProgram();

protected:
	bool checkError();

protected:
	GLuint _program;
	GLuint _vertShader;
	GLuint _fragShader;
	GLuint _tcsShader;
	GLuint _tesShader;
	GLuint _geoShader;
};

NS_CALM_END

#endif // _GLPROGRAM_H_