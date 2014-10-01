#ifndef _DIRECTOR_H_
#define _DIRECTOR_H_

#include "CMMacro.h"
#include "Geometry.h"
#include "c3dmath.h"

NS_CALM_BEGIN

class GLView;

class Director
{
public:
	static Director* Instance();
public:
	Director();
	~Director();

	virtual bool init();

	void setOpenGLView(GLView* view);
	GLView* getOpenGLView() const;

	vmath::mat4 getProjectMatrix() { return _projectMatrix; }

	void setGLDefaultValues();

	bool isExtensionSupported(const char* name);

protected:
	static Director* sm_instance;

	GLView*	_glview;
	Size		_winSizeInPoints;
	vmath::mat4	_projectMatrix;
};

NS_CALM_END

#endif // _DIRECTOR_H_