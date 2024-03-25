#ifndef __MT_COLOR_MODEL_H__
#define __MT_COLOR_MODEL_H__

#include "Model.h"
#include "../ShaderProgram.h"
#include "../buffer/VertexArrayObject.h"

namespace mt {
namespace graphic {

class ColorModel : public Model
{

public:

	// Variables
	static ShaderProgram shader;

	// Constructor
	ColorModel();
	~ColorModel();

	// Load custom
	void loadVAO(std::vector<vec3> vertices, std::vector<unsigned int> indices);

	// General
	void render();

	// Other
	friend class ModelBuilder;

private:

	// Variables
	class ColorModelImpl;
	ColorModelImpl* impl;

};

}}

#endif
