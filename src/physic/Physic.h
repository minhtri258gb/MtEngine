#ifndef __MT_PHYSIC_H__
#define __MT_PHYSIC_H__

#include "body/RigidBody.h"
#include "body/ControlBody.h"

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

	void add(RigidBody*);
	void add(ControlBody*);
	void remove(RigidBody*);
	void remove(ControlBody*);

private:

	// Variable
	class PhysicImpl;
	PhysicImpl* impl;

};

}}

#endif
