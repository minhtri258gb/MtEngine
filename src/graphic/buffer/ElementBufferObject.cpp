#define __MT_ELEMENT_ARRAY_OBJECT_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "ElementBufferObject.h"

using namespace mt;
using namespace mt::graphic;

ElementBufferObject::ElementBufferObject()
{
	this->gl_EBO = -1;
}

ElementBufferObject::~ElementBufferObject()
{
	glDeleteBuffers(1, &this->gl_EBO);
}

void ElementBufferObject::init(std::vector<unsigned int> indices)
{
	glGenBuffers(1, &this->gl_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->gl_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
