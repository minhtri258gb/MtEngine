#define __MT_VERTEX_BUFFER_OBJECT_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "VertexBufferObject.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;

VertexBufferObject::VertexBufferObject()
{
	this->gl_VBO = -1;
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &this->gl_VBO);
}

void VertexBufferObject::init(int location, vector<vec2> _vertices)
{
	glGenBuffers(1, &this->gl_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);
	glEnableVertexAttribArray(location);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::init(int location, vector<vec3> _vertices)
{
	glGenBuffers(1, &this->gl_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);
	glBufferData(GL_ARRAY_BUFFER, 12 * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
	glEnableVertexAttribArray(location);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::init(int location, vector<vec4> _vertices)
{
	glGenBuffers(1, &this->gl_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);
	glBufferData(GL_ARRAY_BUFFER, 16 * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 16, (void*)0);
	glEnableVertexAttribArray(location);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::init(int location, vector<vec4i> _vertices)
{
	glGenBuffers(1, &this->gl_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);
	glBufferData(GL_ARRAY_BUFFER, 16 * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glVertexAttribIPointer(location, 4, GL_INT, 16, (void*)0);
	glEnableVertexAttribArray(location);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::initDynamic(int location, int maxInstance, int type)
{
	glGenBuffers(1, &this->gl_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);

	vector<int> fake;
	fake.resize(maxInstance, type);
	glBufferData(GL_ARRAY_BUFFER, 4 * maxInstance, &fake[0], GL_DYNAMIC_DRAW); // #TODO ko dung fake data
	
	glVertexAttribIPointer(location, 1, GL_INT, 4, (void*)0);
	glVertexAttribDivisor(location, 1);

	glEnableVertexAttribArray(location);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::initDynamic(int location, int maxInstance, vec2 type)
{
	glGenBuffers(1, &this->gl_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);

	vector<vec2> fake;
	fake.resize(maxInstance, type);
	glBufferData(GL_ARRAY_BUFFER, 8 * maxInstance, &fake[0], GL_DYNAMIC_DRAW); // #TODO ko dung fake data
	
	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);
	glVertexAttribDivisor(location, 1);

	glEnableVertexAttribArray(location);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::initDynamic(int location, int maxInstance, vec3 type)
{
	glGenBuffers(1, &this->gl_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);

	vector<vec3> fake;
	fake.resize(maxInstance, type);
	glBufferData(GL_ARRAY_BUFFER, 12 * maxInstance, &fake[0], GL_DYNAMIC_DRAW); // #TODO ko dung fake data
	
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
	glVertexAttribDivisor(location, 1);

	glEnableVertexAttribArray(location);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::initDynamic(int location, int maxInstance, vec4 type)
{
	glGenBuffers(1, &this->gl_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);

	vector<vec4> fake;
	fake.resize(maxInstance, type);
	glBufferData(GL_ARRAY_BUFFER, 16 * maxInstance, &fake[0], GL_DYNAMIC_DRAW); // #TODO ko dung fake data
	
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, 16, (void*)0);
	glVertexAttribDivisor(location, 1);

	glEnableVertexAttribArray(location);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::updateDynamic(vector<int> vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * vertices.size(), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::updateDynamic(vector<vec2> vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * vertices.size(), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::updateDynamic(vector<vec3> vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 12 * vertices.size(), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::updateDynamic(vector<vec4> vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 16 * vertices.size(), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
