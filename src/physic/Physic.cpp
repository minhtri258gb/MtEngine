#define __MT_PHYSIC_CPP__

#include <btBulletDynamicsCommon.h>
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>

#include "common.h"
#include "engine/Timer.h"
#include "engine/file/FileCFG.h"
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

	RigidBody* createPlane(vec3 pos, vec4 plane, float mass);
	RigidBody* createSphere(vec3 pos, float radius, float mass);
	RigidBody* createBox(vec3 pos, quat rot, vec3 scale, float mass);
	RigidBody* createCylinder(vec3 pos, quat rot, vec3 size, float mass);
};

class RigidBody::RigidBodyImpl
{
public:
	btCollisionShape* shape;
	btRigidBody* body;
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

RigidBody* Physic::create(std::string name, vec3 pos, quat rot, vec3 scale)
{
	FileCFG fCFG("./res/models/" + name + "/info.cfg");
	fCFG.select("physic");
	string shape = fCFG.get("shape");
	float mass = fCFG.getFloat("mass");

	RigidBody* body = nullptr;
	if (shape == "box")
	{
		vec3 size = fCFG.getVec3("size");
		size = vec3(size.x*scale.x, size.y*scale.y, size.z*scale.z);
		body = impl->createBox(pos, rot, size, mass);
	}
	else if (shape == "sphere")
	{
		float radius = fCFG.getFloat("radius");
		radius = radius * (scale.x + scale.y + scale.z) / 3.0f;
		body = impl->createSphere(pos, radius, mass);
	}
	else if (shape == "plane")
	{
		vec4 plane = fCFG.getVec4("plane");
		body = impl->createPlane(pos, plane, mass);
	}
	else if (shape == "cylinder")
	{
		vec3 size = fCFG.getVec3("size");
		size = vec3(size.x*scale.x, size.y*scale.y, size.z*scale.z);
		body = impl->createCylinder(pos, rot, size, mass);
	}
	return body;
}

void Physic::add(RigidBody* body)
{
	impl->dynamicsWorld->addRigidBody(body->impl->body);
}

void Physic::remove(RigidBody* body)
{
	impl->dynamicsWorld->removeRigidBody(body->impl->body);
	delete body;
}

RigidBody* Physic::PhysicImpl::createPlane(vec3 pos, vec4 plane, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	
	btVector3 inertia(0, 0, 0);

	bool isDynamic = (mass != 0.f);

	RigidBody* body = new RigidBody();

	body->impl->shape = new btStaticPlaneShape(btVector3(plane.x, plane.y, plane.z), plane.w);
	if (isDynamic)
		body->impl->shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, body->impl->shape, inertia);
	body->impl->body = new btRigidBody(rigidBodyCI);

	return body;
}

RigidBody* Physic::PhysicImpl::createSphere(vec3 pos, float radius, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	
	btVector3 inertia(0, 0, 0);

	bool isDynamic = (mass != 0.f);

	RigidBody* body = new RigidBody();

	body->impl->shape = new btSphereShape(radius);
	if (isDynamic)
		body->impl->shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, body->impl->shape, inertia);
	body->impl->body = new btRigidBody(rigidBodyCI);

	return body;
}

RigidBody* Physic::PhysicImpl::createBox(vec3 pos, quat rot, vec3 scale, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	
	btVector3 inertia(0, 0, 0);

	bool isDynamic = (mass != 0.f);

	RigidBody* body = new RigidBody();

	body->impl->shape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));
	if (isDynamic)
		body->impl->shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, body->impl->shape, inertia);
	body->impl->body = new btRigidBody(rigidBodyCI);

	return body;
}

RigidBody* Physic::PhysicImpl::createCylinder(vec3 pos, quat rot, vec3 size, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	
	btVector3 inertia(0, 0, 0);

	bool isDynamic = (mass != 0.f);

	RigidBody* body = new RigidBody();

	body->impl->shape = new btCylinderShape(btVector3(size.x, size.y, size.z));
	if (isDynamic)
		body->impl->shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, body->impl->shape, inertia);
	body->impl->body = new btRigidBody(rigidBodyCI);

	return body;
}
