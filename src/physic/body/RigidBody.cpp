#define __MT_RIGID_BODY_CPP__

// #define LOG cout << __FILE__ << " | " << __LINE__ << '\n';

#include <btBulletDynamicsCommon.h>
#include <BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h>

#include "common.h"
#include "engine/file/FileCFG.h"
#include "physic/Physic.h"
#include "RigidBody.h"

using namespace std;
using namespace mt;
using namespace mt::physic;

class RigidBody::RigidBodyImpl
{
public:

	// Variable
	btCollisionShape* shape;
	btRigidBody* body;
	bool isAction;

	// Method
	void createPlane(vec3 pos, vec4 plane, float mass);
	void createSphere(vec3 pos, float radius, float mass);
	void createBox(vec3 pos, quat rot, vec3 scale, float mass);
	void createCylinder(vec3 pos, quat rot, vec3 size, float mass);
};

RigidBody::RigidBody()
{
	
	#ifdef LOG
	LOG
	#endif

	// Implement
	impl = new RigidBodyImpl();
	impl->isAction = false;
	
	#ifdef LOG
	LOG
	#endif

}

RigidBody::~RigidBody()
{
	
	#ifdef LOG
	LOG
	#endif

	delete impl->body->getMotionState();
	
	#ifdef LOG
	LOG
	#endif

	delete impl->body;
	
	#ifdef LOG
	LOG
	#endif

	delete impl->shape;

	#ifdef LOG
	LOG
	#endif

	// Implement
	delete impl;
	
	#ifdef LOG
	LOG
	#endif

}

void RigidBody::create(std::string name, vec3 pos, quat rot, vec3 scale)
{
	
	#ifdef LOG
	LOG
	#endif

	FileCFG fCFG("./res/models/" + name + "/info.cfg");
	fCFG.select("physic");
	string shape = fCFG.get("shape");
	float mass = fCFG.getFloat("mass");

	#ifdef LOG
	LOG
	#endif

	impl->body = nullptr;
	if (shape == "box")
	{
		vec3 size = fCFG.getVec3("size");
		size = vec3(size.x*scale.x, size.y*scale.y, size.z*scale.z);
		impl->createBox(pos, rot, size, mass);
	}
	else if (shape == "sphere")
	{
		float radius = fCFG.getFloat("radius");
		radius = radius * (scale.x + scale.y + scale.z) / 3.0f;
		impl->createSphere(pos, radius, mass);
	}
	else if (shape == "plane")
	{
		vec4 plane = fCFG.getVec4("plane");
		impl->createPlane(pos, plane, mass);
	}
	else if (shape == "cylinder")
	{
		vec3 size = fCFG.getVec3("size");
		size = vec3(size.x*scale.x, size.y*scale.y, size.z*scale.z);
		impl->createCylinder(pos, rot, size, mass);
	}
	
	#ifdef LOG
	LOG
	#endif

}

void RigidBody::update()
{

}

void RigidBody::close()
{
	if (impl->isAction)
		Physic::ins.remove(this);
}

void RigidBody::action(bool toogle)
{
	
	#ifdef LOG
	LOG
	#endif

	if (impl->isAction != toogle)
	{
		
		#ifdef LOG
		LOG
		#endif

		impl->isAction = toogle;
		if (toogle)
			Physic::ins.add(this);
		else
			Physic::ins.remove(this);
		
		#ifdef LOG
		LOG
		#endif

	}
	
	#ifdef LOG
	LOG
	#endif

}

void RigidBody::getTransForm(vec3 *origin, quat *angle)
{

	#ifdef LOG
	LOG
	#endif

	btTransform t;
	impl->body->getMotionState()->getWorldTransform(t);

	btVector3 pos = t.getOrigin();
	origin->x = pos.getX();
	origin->y = pos.getY();
	origin->z = pos.getZ();

	btQuaternion rot = t.getRotation();
	*angle = quat(rot.getX(), rot.getY(), rot.getZ(), rot.getW());
	
	#ifdef LOG
	LOG
	#endif

}

vec3 RigidBody::getOrigin()
{
	
	#ifdef LOG
	LOG
	#endif

	btTransform trans;
	impl->body->getMotionState()->getWorldTransform(trans);
	btVector3 origin = trans.getOrigin();
	return vec3(origin.getX(), origin.getY(), origin.getZ());
	
	#ifdef LOG
	LOG
	#endif

}

void RigidBody::RigidBodyImpl::createPlane(vec3 pos, vec4 plane, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	
	btVector3 inertia(0, 0, 0);

	bool isDynamic = (mass != 0.f);

	this->shape = new btStaticPlaneShape(btVector3(plane.x, plane.y, plane.z), plane.w);
	if (isDynamic)
		this->shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, this->shape, inertia);
	this->body = new btRigidBody(rigidBodyCI);
}

void RigidBody::RigidBodyImpl::createSphere(vec3 pos, float radius, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	
	btVector3 inertia(0, 0, 0);

	bool isDynamic = (mass != 0.f);

	this->shape = new btSphereShape(radius);
	if (isDynamic)
		this->shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, this->shape, inertia);
	this->body = new btRigidBody(rigidBodyCI);
}

void RigidBody::RigidBodyImpl::createBox(vec3 pos, quat rot, vec3 scale, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	
	btVector3 inertia(0, 0, 0);

	bool isDynamic = (mass != 0.f);

	RigidBody* body = new RigidBody();

	this->shape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));
	if (isDynamic)
		this->shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, this->shape, inertia);
	this->body = new btRigidBody(rigidBodyCI);
}

void RigidBody::RigidBodyImpl::createCylinder(vec3 pos, quat rot, vec3 size, float mass)
{
	btTransform transform;
	transform.setIdentity();
	transform.setRotation(btQuaternion(rot.x, rot.y, rot.z, rot.w));
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	
	btVector3 inertia(0, 0, 0);

	bool isDynamic = (mass != 0.f);

	RigidBody* body = new RigidBody();

	this->shape = new btCylinderShape(btVector3(size.x, size.y, size.z));
	if (isDynamic)
		this->shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, this->shape, inertia);
	this->body = new btRigidBody(rigidBodyCI);
}
