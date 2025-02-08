#define __MT_RIGID_BODY_CPP__

#include <reactphysics3d/reactphysics3d.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "engine/file/FileCFG.h"
#include "physic/Physic.h"
#include "RigidBody.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::physic;
namespace rp3 = reactphysics3d;


class Physic::PhysicImpl {
public:
	rp3::PhysicsCommon common;
	rp3::PhysicsWorld* world;
};
class RigidBody::RigidBodyImpl {
public:
	rp3::RigidBody* body; // Cơ thể
	rp3::Collider* collider; // Bộ phận
};

RigidBody::RigidBody() {
	LOG("RigidBody");
	try {

		// Implement
		impl = new RigidBodyImpl();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
RigidBody::~RigidBody() {
	LOG("~RigidBody");

	// Implement
	delete this->impl;
}

void RigidBody::update() {
	LOG("update");
	try {

		// const dReal* pos = dBodyGetPosition(impl->body);
		// std::cout << "Body position: x = " << pos[0] << ", y = " << pos[1] << ", z = " << pos[2] << std::endl;

		// // Áp dụng lực hấp dẫn
		// dMass mass;
		// dBodyGetMass(impl->body, &mass);
		// dBodyAddForce(impl->body, 0, -9.8 * mass.mass, 0);

	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void RigidBody::clear() {
	LOG("close");
	try {
		if (impl->body != nullptr)
			Physic::ins.impl->world->destroyRigidBody(impl->body);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void RigidBody::action(bool toogle) {
	LOG("action");
	try {

		// if (impl->body == nullptr)
		// 	return;

		// bool curToogle = dBodyIsEnabled(impl->body);
		// if (curToogle = toogle)
		// 	return;

		// if (toogle)
		// 	dBodyEnable(impl->body);
		// else
		// 	dBodyDisable(impl->body);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void RigidBody::getTransForm(vec3 *origin, quat *angle) {
	LOG("getTransForm");
	try {

		if (impl->body == nullptr)
			throw error("BODY_NULL", "Chua khoi tao body!");

		const rp3::Transform& transform = impl->body->getTransform();
		const rp3::Vector3& position = transform.getPosition();
		const rp3::Quaternion& rotate = transform.getOrientation();

		origin->set(position.x, position.y, position.z);
		angle->set(rotate.x, rotate.y, rotate.z, rotate.w);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
vec3 RigidBody::getOrigin() {
	LOG("getOrigin");
	try {

		if (impl->body == nullptr)
			throw error("BODY_NULL", "Chua khoi tao body!");

		const rp3::Transform& transform = impl->body->getTransform();
		const rp3::Vector3& position = transform.getPosition();

		return vec3(position.x, position.y, position.z);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void RigidBody::force(vec3 velocity) { // Áp dụng lực
	LOG("force");
	try {
		impl->body->applyLocalForceAtCenterOfMass(rp3::Vector3(velocity.x, velocity.y, velocity.z));
		// impl->body->applyWorldForceAtCenterOfMass(rp3::Vector3(velocity.x, velocity.y, velocity.z));
		
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void RigidBody::setVelocity(vec3 velocity) { // Áp dụng lực
	LOG("setVelocity");
	try {
		impl->body->setLinearVelocity(rp3::Vector3(velocity.x, velocity.y, velocity.z));
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
