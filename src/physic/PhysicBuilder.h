#ifndef __MT_PHYSIC_BUILDER_H__
#define __MT_PHYSIC_BUILDER_H__

#include "engine/data/HeightmapData.h"
#include "body/RigidBody.h"

namespace mt {
namespace physic {

class PhysicBuilder {

public:

	// Forwards
	PhysicBuilder();
	~PhysicBuilder();

	// Native
	RigidBody* load(std::string name, vec3 pos, quat rot, vec3 scale);

	// RigidBody* createBox(vec3 pos, quat rot, vec3 size);
	// RigidBody* createSphere(vec3 pos, float radius);
	// RigidBody* createCapsule(vec3 pos, float radius, float height);

	RigidBody* createPlayer(vec3 pos);
	RigidBody* createHeightField(engine::HeightmapData* data, float cellScale);

private:

	// Variables
	class PhysicBuilderImpl;
	PhysicBuilderImpl* impl;

};

}}

#endif
