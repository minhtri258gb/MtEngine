#define __MT_CONTROL_BODY_CPP__

#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "common.h"
#include "physic/Physic.h"
#include "ControlBody.h"

using namespace std;
using namespace mt;
using namespace mt::physic;


class ControlBody::ControlBodyImpl
{
public:
	btPairCachingGhostObject *ghostObject;
	btKinematicCharacterController* controller;

	bool isAction;

	// Method
	void initCapsule(vec3 origin);
};

ControlBody::ControlBody()
{
	// Implement
	impl = new ControlBodyImpl();
	impl->isAction = false;
}

ControlBody::~ControlBody()
{
	// if (impl->isAction)
	// 	Physic::ins.remove(this);
	
	// delete impl->body->getMotionState();
	// delete impl->body;
	// delete impl->shape;

	// Implement
	delete impl;
}

void ControlBody::createCapsule(vec3 origin)
{
	impl->initCapsule(origin);
}

void ControlBody::close()
{
	delete impl->ghostObject->getCollisionShape();
	delete impl->ghostObject;
	delete impl->controller;
}

void ControlBody::update()
{

}

void ControlBody::action(bool toogle)
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

void ControlBody::getTransForm(vec3 *origin, quat *angle)
{
	// btTransform t;
	// impl->body->getMotionState()->getWorldTransform(t);

	// btVector3 pos = t.getOrigin();
	// origin->x = pos.getX();
	// origin->y = pos.getY();
	// origin->z = pos.getZ();

	// btQuaternion rot = t.getRotation();
	// *angle = quat(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
}

vec3 ControlBody::getOrigin()
{
	btVector3 origin = impl->controller->getGhostObject()->getWorldTransform().getOrigin();
	return vec3(origin.getX(), origin.getY(), origin.getZ());
}

void ControlBody::setOrigin(vec3 origin)
{
	impl->controller->getGhostObject()->getWorldTransform().setOrigin(btVector3(origin.x, origin.y, origin.z));
}

void ControlBody::setGravity(float gravity)
{
	impl->controller->setGravity(btVector3(0, 0, -gravity));
}

void ControlBody::setWalkDirection(vec3 velocity)
{
	impl->controller->setWalkDirection(btVector3(velocity.x, velocity.y, velocity.z));
}

void ControlBody::setLinearVelocity(vec3 velocity)
{
	impl->controller->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}

void ControlBody::jump(float force)
{
	impl->controller->setJumpSpeed(force);
	if (impl->controller->canJump())
		impl->controller->jump();
}

bool ControlBody::onGround()
{
	return impl->controller->onGround();
}

void ControlBody::ControlBodyImpl::initCapsule(vec3 origin)
{
	btConvexShape *ghostShape = new btCapsuleShapeZ(10.0f, 48.0f); // 68
	
	this->ghostObject = new btPairCachingGhostObject();
	this->ghostObject->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(origin.x, origin.y, origin.z)));
	this->ghostObject->setCollisionShape(ghostShape);
	this->ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	
	this->controller = new btKinematicCharacterController(ghostObject, ghostShape, 25, btVector3(0, 1, 0));
	this->controller->setUseGhostSweepTest(false);
	this->controller->setUpInterpolate(true);
	this->controller->setAngularDamping(1);
	this->controller->setFallSpeed(1024);
	this->controller->setGravity(btVector3(0, -1024, 0)); // #TODO config
	this->controller->warp(btVector3(origin.x, origin.y, origin.z));
}
