#ifndef __MT_COLOR_MODEL_H__
#define __MT_COLOR_MODEL_H__

#include "Model.h"
#include "../ShaderProgram.h"
#include "../buffer/VertexArrayObject.h"

namespace mt {
namespace graphic {

class ColorModel : public Model {

public:

	// Variables
	static ShaderProgram shader;

	// Constructor
	ColorModel(std::string name);
	~ColorModel();

	// Load custom
	void loadVAO(
		std::vector<vec3> vertices,
		std::vector<vec4> colors,
		// std::vector<vec3> normals,
		std::vector<unsigned int> indices
	);

	// General
	void render(vec3 pos, quat rot, vec3 scale);

	// Other
	friend class ModelBuilder;

private:

	// Variables
	class ColorModelImpl;
	ColorModelImpl* impl;

};

}}

#endif
