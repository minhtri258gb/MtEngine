#ifndef __MT_SIMPLE_MODEL_H__
#define __MT_SIMPLE_MODEL_H__

#include "Model.h"
#include "../ShaderProgram.h"

namespace mt {
namespace graphic {

class SimpleModel : public Model
{

public:

	// Variables
	static ShaderProgram shader;

	// Constructor
	SimpleModel();
	~SimpleModel();

	// Load custom
	void loadVAO(std::vector<vec3> vertices, std::vector<vec2> texcoords, std::vector<vec3> normals, std::vector<unsigned int> indices);
	void loadVAO(std::vector<vec3> vertices, std::vector<vec2> texcoords, std::vector<unsigned int> indices);
	void loadVAO(std::vector<vec3> vertices, std::vector<unsigned int> indices);
	void loadTexture(std::string filepath);

	// General
	void render(vec3 pos, quat rot, vec3 scale);

	// Other
	friend class ModelBuilder;

private:

	// Variables
	class SimpleModelImpl;
	SimpleModelImpl* impl;

};

}}

#endif
