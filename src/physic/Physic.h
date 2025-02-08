#ifndef __MT_PHYSIC_H__
#define __MT_PHYSIC_H__

#include "PhysicBuilder.h"

namespace mt {
namespace physic {

class RigidBody;
class PhysicBuilder;

class Physic {
public:

	// Variable
	static Physic ins;
	PhysicBuilder builder;

	// General
	Physic();
	~Physic();

	// Static
	static void cbkInteract();

	// Native
	void init();
	void update();
	void close();

private:

	// Variable
	class PhysicImpl;
	PhysicImpl* impl;

	friend class RigidBody;
	friend class PhysicBuilder;

};

}}

#endif
