#ifndef __MT_ENTITY_H__
#define __MT_ENTITY_H__

namespace mt {
namespace game {

class Entity
{

public:

	// Variable
	vec3 position;

	// Forward
	Entity();
	virtual ~Entity();
	virtual void update();
	virtual void render();

};

}}

#endif
