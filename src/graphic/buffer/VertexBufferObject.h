#ifndef __MT_VERTEX_BUFFER_OBJECT_H__
#define __MT_VERTEX_BUFFER_OBJECT_H__

namespace mt {
namespace graphic {

class VertexBufferObject
{

public:

	// Variable
	unsigned int gl_VBO;

	// Forward
	VertexBufferObject();
	~VertexBufferObject();
	void init(int location, std::vector<vec2> vertices);
	void init(int location, std::vector<vec3> vertices);
	void init(int location, std::vector<vec4> vertices);
	void init(int location, std::vector<vec4i> vertices);
	void initDynamic(int location, int maxInstance, int type);
	void initDynamic(int location, int maxInstance, float type);
	void initDynamic(int location, int maxInstance, vec2 type);
	void initDynamic(int location, int maxInstance, vec3 type);
	void initDynamic(int location, int maxInstance, vec4 type);
	void updateDynamic(std::vector<int> vertices);
	void updateDynamic(std::vector<float> vertices);
	void updateDynamic(std::vector<vec2> vertices);
	void updateDynamic(std::vector<vec3> vertices);
	void updateDynamic(std::vector<vec4> vertices);

	// Native
	void bind();
	void unbind();

};

}}

#endif
