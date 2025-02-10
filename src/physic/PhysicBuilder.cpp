#define __MT_PHYSIC_BUILDER_CPP__

/**
 * https://www.reactphysics3d.com/documentation/index.html
 */

#include <reactphysics3d/reactphysics3d.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "engine/Timer.h"
#include "engine/file/FileCFG.h"
#include "engine/utils/StringUtils.h"
#include "PhysicBuilder.h"
#include "Physic.h"

using namespace std;
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
	rp3::RigidBody* body;
	rp3::Collider* collider;
};
class PhysicBuilder::PhysicBuilderImpl {
public:
	void checkError(vector<rp3d::Message>);
};


PhysicBuilder::PhysicBuilder() {
	LOG("PhysicBuilder");
	try {

		// Impliment
		impl = new PhysicBuilderImpl();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
PhysicBuilder::~PhysicBuilder() {
	LOG("~PhysicBuilder");

	// Impliment
	delete impl;
}

RigidBody* PhysicBuilder::load(std::string name, vec3 pos, quat rot, vec3 scale) {
	LOG("loadBody");
	try {

		FileCFG fCFG("./res/models/" + name + "/info.cfg");
		fCFG.select("physic");

		// Create Body with Tranform
		rp3::Vector3 position(pos.x, pos.y, pos.z);
		rp3::Quaternion orientation(rot.x, rot.y, rot.z, rot.w);
		rp3::Transform transform(position, orientation);
		rp3::RigidBody* body = Physic::ins.impl->world->createRigidBody(transform);

			// Create Shape
		string shapeType = fCFG.get("shape");
		rp3::CollisionShape* shape = nullptr;
		if (shapeType == "box") {
			vec3 size = fCFG.getVec3("size");
			size = vec3(size.x*scale.x, size.y*scale.y, size.z*scale.z);
			const rp3::Vector3 halfExtents(size.x/2, size.y/2, size.z/2);
			shape = Physic::ins.impl->common.createBoxShape(halfExtents);
		}
		else if (shapeType == "sphere") {
			float radius = fCFG.getFloat("radius");
			shape = Physic::ins.impl->common.createSphereShape(radius);
		}
		else if (shapeType == "capsule") {
			float radius = fCFG.getFloat("radius");
			float height = fCFG.getFloat("height");
			shape = Physic::ins.impl->common.createCapsuleShape(radius, height);
		}
		else
			throw error("TYPE_INVAIL", "Body type cau hinh ko hop le! " + shapeType);

		// Create Collider
		rp3::Transform transformLocal = rp3::Transform::identity();
		rp3::Collider* collider = body->addCollider(shape, transformLocal);

		// Set Mass
		float mass = fCFG.getFloat("mass");
		body->setMass(mass);
		if (mass == 0.0f) {
			body->setType(rp3::BodyType::STATIC);
			body->enableGravity(false);
		}
		else {
			body->setType(rp3::BodyType::DYNAMIC); // DYNAMIC, KINEMATIC
			body->enableGravity(true);
		}

		// Friction
		float friction = fCFG.getFloat("friction");
		body->setLinearDamping(friction);
		body->setAngularDamping(friction);

		// Create RigidBody
		RigidBody* resBody = new RigidBody();
		resBody->impl->body = body;
		resBody->impl->collider = collider;
		return resBody;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

RigidBody* PhysicBuilder::createPlayer(vec3 pos) {
	LOG("createPlayer");
	try {

		const float radius = 1.0f;
		const float height = 2.0f;
		const float mass = 1.0f;

		// Create Body with Tranform
		rp3::Transform transform = rp3::Transform::identity();
		transform.setPosition(rp3::Vector3(pos.x, pos.y, pos.z));
		rp3::RigidBody* body = Physic::ins.impl->world->createRigidBody(transform);

		// Create Shape
		rp3::CapsuleShape* shape = Physic::ins.impl->common.createCapsuleShape(radius, height);
		rp3::Transform transformLocal = rp3::Transform::identity();
		rp3::Collider* collider = body->addCollider(shape, transformLocal);

		// Attribute
		body->setType(rp3::BodyType::DYNAMIC); // DYNAMIC, KINEMATIC
		body->setMass(mass);
		body->setAngularLockAxisFactor(rp3::Vector3(0, 1, 0));
		body->enableGravity(false);
		body->setLinearDamping(1);
		body->setAngularDamping(1);

		// Create RigidBody
		RigidBody* resBody = new RigidBody();
		resBody->impl->body = body;
		resBody->impl->collider = collider;
		return resBody;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

RigidBody* PhysicBuilder::createHeightField(HeightmapData* data, float cellScale) {
	LOG("createHeightField");
	try {

		int col = data->getWidth();
		int row = data->getDepth();

		// Convert data
		vector<float> heightData = data->getHeightData();
		for (uint i=0, size=heightData.size(); i<size; i++) {
			// heightData[i] = heightData[i] * 1.0f;
			heightData[i] = heightData[i] * data->getScale();
			// heightData[i] = heightData[i] * data->getScale() - data->getOffset();
		}

		// Create HeightField
		vector<rp3d::Message> messages;
		rp3d::HeightField* heightField = Physic::ins.impl->common.createHeightField(
			col, row, &heightData[0],
			rp3d::HeightField::HeightDataType::HEIGHT_FLOAT_TYPE,
			messages
		);
		impl->checkError(messages);

		if (heightField == nullptr)
			throw error("CREATE_HEIGHFIELD_FAILD", "heightField is Null");

		// Create HeightFieldShape
		rp3d::HeightFieldShape* heightFieldShape = Physic::ins.impl->common.createHeightFieldShape(heightField);

		// Nâng địa hình lên mức từ 0 trở lên, Bắt đầu địa hình ở trên bên trái
		rp3::Transform transform = rp3::Transform::identity();
		transform.setPosition(rp3::Vector3(col/2, data->getScale() / 2.0f + data->getOffset(), row/2));
		// transform.setPosition(rp3::Vector3(col/2, data->getScale() / 2.0f, row/2));
		// transform.setPosition(rp3::Vector3(col/2, data->getScale() / 2.0f - data->getOffset(), row/2));

		// Create Body
		rp3::RigidBody* body = Physic::ins.impl->world->createRigidBody(transform);

		// Create Shape
		rp3::Transform transformLocal = rp3::Transform::identity();
		rp3::Collider* collider = body->addCollider(heightFieldShape, transformLocal);

		// Attribute
		body->setType(rp3::BodyType::STATIC);
		body->setMass(0.0f);
		body->enableGravity(false);

		// Create RigidBody
		RigidBody* resBody = new RigidBody();
		resBody->impl->body = body;
		resBody->impl->collider = collider;
		return resBody;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void PhysicBuilder::PhysicBuilderImpl::checkError(vector<rp3d::Message> messages) {
	LOG("checkError");
	try {

		if (messages.size() == 0)
			return;

		string errMsg = "";
		for (const rp3d::Message& message: messages) {
			string messageType;
			switch (message.type) {
				case rp3d::Message::Type::Information: messageType = "info"; break;
				case rp3d::Message::Type::Warning: messageType = "warning"; break;
				case rp3d::Message::Type::Error: messageType = "error"; break;
			}
			errMsg += "["+messageType+"] " + message.text + "\n";
		}

		throw error("REACT_PHYSIC_3D_ERROR", errMsg);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}