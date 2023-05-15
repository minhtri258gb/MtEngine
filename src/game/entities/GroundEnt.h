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

	// Variable
	graphic::Model* model;
	physic::RigidBody* body;

	// Forward
	GroundEnt(std::string name);
	~GroundEnt();
	void update();
	void render();

	// Native

};

}}

#endif
