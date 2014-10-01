#include "Object3D.h"

NS_CALM_BEGIN

Object3D::Object3D()
	: _vertexBuffer(0)
	, _indexBuffer(0)
	, _vao(0)
	, _instanceCount(1)
	, _baseInstance(0)
{
}

Object3D::~Object3D()
{
	free();
}

void Object3D::load(const char* filename)
{
	this->free();

	FILE* f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	size_t fileSize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* data = new char[fileSize];
	fread(data, fileSize, sizeof(char), f);

	char* ptr = data;
	SBM_HEARDER* header = (SBM_HEARDER*)ptr;
	ptr += header->size;

	SBM_VERTEX_ATTRIB_CHUNK* vertexAttribChunk = nullptr;
	SBM_CHUNK_VERTEX_DATA* vertexDataChunk = nullptr;
	SBM_CHUNK_INDEX_DATA* indexDataChunk = nullptr;
	SBM_CHUNK_SUB_OBJECT_LIST* subObjectChunk = nullptr;

	for (unsigned int i = 0; i < header->num_chunks; i++) {
		SBM_CHUNK_HEADER* chunk = (SBM_CHUNK_HEADER*)ptr;
		ptr += chunk->size;
		switch (chunk->chunk_type) {
		case SB6M_CHUNK_TYPE_VERTEX_ATTRIBS:
			vertexAttribChunk = (SBM_VERTEX_ATTRIB_CHUNK*)chunk;
			break;
		case SB6M_CHUNK_TYPE_VERTEX_DATA:
			vertexDataChunk = (SBM_CHUNK_VERTEX_DATA*)chunk;
			break;
		case SB6M_CHUNK_TYPE_INDEX_DATA:
			indexDataChunk = (SBM_CHUNK_INDEX_DATA*)chunk;
			break;
		case SB6M_CHUNK_TYPE_SUB_OBJECT_LIST:
			subObjectChunk = (SBM_CHUNK_SUB_OBJECT_LIST*)chunk;
			break;
		default:
			break; // goto failed;
		}
	}

	// failed:
	if (subObjectChunk != nullptr) {
		if (subObjectChunk->count > MAX_SUB_OBJECTS) {
			subObjectChunk->count = MAX_SUB_OBJECTS;
		}

		for (unsigned int i = 0; i < subObjectChunk->count; i++) {
			sub_object[i] = subObjectChunk->sub_object[i];
		}

		num_sub_objects = subObjectChunk->count;
	}
	else {
		sub_object[0].first = 0;
		sub_object[0].count = vertexDataChunk->total_vertices;
		num_sub_objects = 1;
	}

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexDataChunk->data_size,
		data + vertexDataChunk->data_offset, GL_STATIC_DRAW);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	for (unsigned int i = 0; i < vertexAttribChunk->attrib_count; ++i) {
		SBM_VERTEX_ATTRIB_DECL& attrib = vertexAttribChunk->attrib_data[i];
		glVertexAttribPointer(i,
			attrib.size,
			attrib.type,
			attrib.flags & SB6M_VERTEX_ATTRIB_FLAG_NORMALIZED ? GL_TRUE : GL_FALSE,
			attrib.stride,
			(GLvoid*)(uintptr_t)attrib.data_offset);
		glEnableVertexAttribArray(i);
	}

	// ¶¥µã
	if (indexDataChunk != nullptr) {
		glGenVertexArrays(1, &_indexBuffer);
		glBindVertexArray(_indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indexDataChunk->index_count * (indexDataChunk->index_type == GL_UNSIGNED_SHORT ? sizeof(GLushort) : sizeof(GLubyte)),
			data + indexDataChunk->index_data_offset, GL_STATIC_DRAW);

		_numIndices = indexDataChunk->index_count;
		_indexType = indexDataChunk->index_type;
	}
	else {
		_numIndices = vertexDataChunk->total_vertices;
	}

	delete[] data;
	fclose(f);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object3D::free()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_indexBuffer);

	_vao = 0;
	_vertexBuffer = 0;
	_indexBuffer = 0;
	_numIndices = 0;
}

void Object3D::render(double time)
{
	this->renderSubObject(0);
}

void Object3D::renderSubObject(unsigned int objectIdx)
{
	glBindVertexArray(_vao);
	if (_indexBuffer != 0) {
		glDrawElementsInstancedBaseInstance(GL_TRIANGLES, _numIndices, _indexType, 0,
			_instanceCount, _baseInstance);
	}
	else {
		glDrawArraysInstancedBaseInstance(GL_TRIANGLES, sub_object[objectIdx].first,
			sub_object[objectIdx].count, _instanceCount, _baseInstance);
	}
}

void Object3D::getSubObjectInfo(unsigned int idx, GLuint& first, GLuint& count)
{
	if (idx >= num_sub_objects) {
		first = 0;
		count = 0;
	}
	else {
		first = sub_object[idx].first;
		count = sub_object[idx].count;
	}
}

NS_CALM_END
