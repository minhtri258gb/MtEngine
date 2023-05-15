#define __MT_RIGID_BODY_CPP__

#include <btBulletDynamicsCommon.h>
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>

#include "common.h"
#include "../Physic.h"
#include "RigidBody.h"

using namespace std;
using namespace mt;
using namespace mt::physic;

class RigidBody::RigidBodyImpl
{
public:
	btCollisionShape* shape;
	btRigidBody* body;

	bool isAction;
};

RigidBody::RigidBody()
{
	// Implement
	this->impl = new RigidBodyImpl();
}

RigidBody::~RigidBody()
{
	if (impl->isAction)
		Physic::ins.remove(this);
	
	delete impl->body->getMotionState();
	delete impl->body;
	delete impl->shape;

	// Implement
	delete this->impl;
}

void RigidBody::initPlane()
{
	impl->isAction = false;

	impl->shape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0, motionState, impl->shape, btVector3(0, 0, 0));
	impl->body = new btRigidBody(rigidBodyCI);
}

void RigidBody::initSphere()
{
	impl->isAction = false;

	impl->shape = new btSphereShape(1);
	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 inertia(0, 0, 0);
	impl->shape->calculateLocalInertia(mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, impl->shape, inertia);
	impl->body = new btRigidBody(rigidBodyCI);
}

void RigidBody::close()
{
	
}

void RigidBody::update()
{

}

void RigidBody::action(bool toogle)
{
	if (impl->isAction != toogle)
	{
		impl->isAction = toogle;
		if (toogle)
			Physic::ins.add(this);
		else
			Physic::ins.remove(this);
	}
}

vec3 RigidBody::getOrigin()
{
	btTransform trans;
	impl->body->getMotionState()->getWorldTransform(trans);
	btVector3 origin = trans.getOrigin();
	return vec3(origin.getX(), origin.getY(), origin.getZ());
}
