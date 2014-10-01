#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "Common.h"
#include "ObjectDefine.h"

NS_CALM_BEGIN

class Object3D
{
public:
	Object3D();
	~Object3D();

	virtual void render(double time);

	void free();
	void load(const char* filename);
	GLuint get_vao() const { return _vao; }
	unsigned int get_sub_object_count() const { return num_sub_objects; }
	void getSubObjectInfo(unsigned int idx, GLuint &first, GLuint &count);

protected:
	void renderSubObject(unsigned int objectIdx);

private:
	GLuint  _vertexBuffer;
	GLuint  _indexBuffer;
	GLuint  _vao;
	GLuint  _numIndices;
	GLuint  _indexType;

	unsigned int _instanceCount;
	unsigned int _baseInstance;

	enum { MAX_SUB_OBJECTS = 256 };

	unsigned int            num_sub_objects;
	SB6M_SUB_OBJECT_DECL    sub_object[MAX_SUB_OBJECTS];
};

NS_CALM_END

#endif // _OBJECT3D_H_