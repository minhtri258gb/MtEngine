#define __MT_PHYSIC_CPP__

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>

#include "common.h"
#include "engine/Timer.h"
#include "Physic.h"

using namespace std;
using namespace mt::engine;
using namespace mt::physic;

Physic Physic::ins;

class Physic::PhysicImpl
{
public:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btSequentialImpulseConstraintSolver* solver;
};

class RigidBody::RigidBodyImpl
{
public:
	btCollisionShape* shape;
	btRigidBody* body;
	bool isAction;
};

class ControlBody::ControlBodyImpl
{
public:
	btPairCachingGhostObject *ghostObject;
	btKinematicCharacterController* controller;
	bool isAction;
};

Physic::Physic()
{
	// Impliment
	this->impl = new PhysicImpl();
}

Physic::~Physic()
{
	// Impliment
	delete this->impl;
}

void Physic::init()
{
	impl->broadphase = new btDbvtBroadphase();
	impl->collisionConfiguration = new btDefaultCollisionConfiguration();
	impl->dispatcher = new btCollisionDispatcher(impl->collisionConfiguration);
	// btGImpactCollisionAlgorithm::registerAlgorithm(impl->dispatcher);
	impl->solver = new btSequentialImpulseConstraintSolver;
	impl->dynamicsWorld = new btDiscreteDynamicsWorld(impl->dispatcher, impl->broadphase, impl->solver, impl->collisionConfiguration);
	impl->dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
}

void Physic::close()
{
	delete impl->dynamicsWorld;
	delete impl->solver;
	delete impl->dispatcher;
	delete impl->collisionConfiguration;
	delete impl->broadphase;
}

void Physic::update()
{
	impl->dynamicsWorld->stepSimulation(Timer::ins.getTimePassed(), 1);
}

void Physic::add(RigidBody* body)
{
	impl->dynamicsWorld->addRigidBody(body->impl->body);
}

void Physic::add(ControlBody* body)
{
	impl->dynamicsWorld->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	impl->dynamicsWorld->addCollisionObject(body->impl->ghostObject, btBroadphaseProxy::CharacterFilter,
			btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
	impl->dynamicsWorld->addAction(body->impl->controller);
}

void Physic::remove(RigidBody* body)
{
	impl->dynamicsWorld->removeRigidBody(body->impl->body);
}

void Physic::remove(ControlBody* body)
{
	impl->dynamicsWorld->removeCollisionObject(body->impl->ghostObject);
	impl->dynamicsWorld->removeAction(body->impl->controller);
}
