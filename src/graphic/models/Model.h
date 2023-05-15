#ifndef __MT_MODEL_H__
#define __MT_MODEL_H__

namespace mt {
namespace graphic {

class Model
{

public:

	// Variables
	vec3 position;
	quat angle;
	vec3 scale;

	// Forwards
	Model();
	virtual ~Model();
	virtual void render();

	// Natives

};

}}

#endif
