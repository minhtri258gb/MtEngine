#ifndef __MT_VERTEX_ARRAY_OBJECT_H__
#define __MT_VERTEX_ARRAY_OBJECT_H__

#include "VertexBufferObject.h"
#include "ElementBufferObject.h"

namespace mt {
namespace graphic {

class VertexArrayObject
{

public:

	// Variable

	// Forward
	VertexArrayObject();
	~VertexArrayObject();
	void init();

	void addAttribute(std::vector<vec2> data);
	void addAttribute(std::vector<vec3> data);
	void addAttribute(std::vector<vec4> data);
	void addAttribute(std::vector<vec4i> data);

	void addDynamicAttribute(int maxInstance, int type);
	void addDynamicAttribute(int maxInstance, vec2 type);
	void addDynamicAttribute(int maxInstance, vec3 type);
	void addDynamicAttribute(int maxInstance, vec4 type);

	void updateDynamicAttribute(int location, std::vector<int> data);
	void updateDynamicAttribute(int location, std::vector<vec2> data);
	void updateDynamicAttribute(int location, std::vector<vec3> data);
	void updateDynamicAttribute(int location, std::vector<vec4> data);

	void addIndices(std::vector<unsigned int> indices);

	// Native
	void bind();
	void unbind();

	void drawPoints();
	void drawPointInstance(int num);
	void drawTriangle();
	void drawTriangleTrip();
	void drawPatches();
	void drawPatchesInstance(int num);
	void drawElementTriangle();
	
	int getCount();
	void setCount(int count);

private:

	// Variable
	unsigned int gl_VAO;
	std::vector<VertexBufferObject*> VBOs;
	ElementBufferObject *EBO;
	int count;

};

}}

#endif
