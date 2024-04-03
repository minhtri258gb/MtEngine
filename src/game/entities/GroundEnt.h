#ifndef __MT_GROUND_ENTITY_H__
#define __MT_GROUND_ENTITY_H__

#include "Entity.h"
#include "graphic/models/Model.h"
#include "physic/body/RigidBody.h"

namespace mt {
namespace game {

class GroundEnt : public Entity
{

public:

	// Forward
	GroundEnt(std::string name);
	~GroundEnt();
	void init();
	void update();

	// Native

private:

	// Impliment
	class GroundEntImpl;
	GroundEntImpl* impl;

};

}}

#endif
