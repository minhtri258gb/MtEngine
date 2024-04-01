#ifndef __MT_PHYSIC_H__
#define __MT_PHYSIC_H__

#include "body/RigidBody.h"

namespace mt {
namespace physic {

class Physic
{
public:

	// Variable
	static Physic ins;

	// General
	Physic();
	~Physic();

	void init();
	void close();

	void update();

	RigidBody* createPlane(vec3 pos, vec3 normal, float scale, float mass);
	RigidBody* createSphere(vec3 pos, float radius, float mass);
	RigidBody* createBox(vec3 pos, quat rot, vec3 scale, float mass);
	
	void add(RigidBody*);
	void remove(RigidBody*);

private:

	// Variable
	class PhysicImpl;
	PhysicImpl* impl;

};

}}

#endif
