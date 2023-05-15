#ifndef __MT_SIMPLE_MODEL_H__
#define __MT_SIMPLE_MODEL_H__

#include "Model.h"
#include "../ShaderProgram.h"
#include "../buffer/VertexArrayObject.h"
#include "../texture/Texture.h"

namespace mt {
namespace graphic {

class SimpleModel : public Model
{

public:

	// Variables
	static ShaderProgram shader;

	// Forwards
	SimpleModel();
	~SimpleModel();
	void render();

	// Natives

	// Other
	friend class ModelBuilder;

private:

	// Variables
	VertexArrayObject VAO;
	Texture texture;

};

}}

#endif
