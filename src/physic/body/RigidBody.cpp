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
	impl = new RigidBodyImpl();
	impl->isAction = false;
}

RigidBody::~RigidBody()
{
	if (impl->isAction)
		Physic::ins.remove(this);
	
	delete impl->body->getMotionState();
	delete impl->body;
	delete impl->shape;

	// Implement
	delete impl;
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

void RigidBody::getTransForm(vec3 *origin, quat *angle)
{
	btTransform t;
	impl->body->getMotionState()->getWorldTransform(t);

	btVector3 pos = t.getOrigin();
	origin->x = pos.getX();
	origin->y = pos.getY();
	origin->z = pos.getZ();

	btQuaternion rot = t.getRotation();
	*angle = quat(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
}

vec3 RigidBody::getOrigin()
{
	btTransform trans;
	impl->body->getMotionState()->getWorldTransform(trans);
	btVector3 origin = trans.getOrigin();
	return vec3(origin.getX(), origin.getY(), origin.getZ());
}
