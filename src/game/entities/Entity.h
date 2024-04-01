#ifndef __MT_ENTITY_H__
#define __MT_ENTITY_H__

namespace mt {
namespace game {

class Entity
{

public:

	// Variables
	std::string name;
	vec3 pos;
	quat rot;
	vec3 scale;

	// Forward
	Entity();
	virtual ~Entity();
	virtual void update();
	virtual void render();

};

}}

#endif
