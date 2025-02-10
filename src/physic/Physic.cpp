#define __MT_PHYSIC_CPP__

/**
 * https://www.reactphysics3d.com/documentation/index.html
 */

#include <reactphysics3d/reactphysics3d.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "engine/Timer.h"
#include "engine/utils/StringUtils.h"
#include "Physic.h"

using namespace std;
using namespace mt::engine;
using namespace mt::physic;
namespace rp3 = reactphysics3d;


Physic Physic::ins;

class Physic::PhysicImpl {
public:
	rp3::PhysicsCommon common;
	rp3::PhysicsWorld* world;
};


Physic::Physic() {
	LOG("Physic");
	try {

		// Impliment
		impl = new PhysicImpl();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
Physic::~Physic() {
	LOG("~Physic");

	// Impliment
	delete impl;
}

void Physic::init() {
	LOG("init");
	try {

		// Tạo thế giới
		impl->world = impl->common.createPhysicsWorld();

		// Trọng lực
		float gravity = Config::ins.physic_gravity;
		impl->world->setGravity(reactphysics3d::Vector3(0, -gravity, 0));
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Physic::update() {
	// static int i = 0;
	// LOG(StringUtils::format("update: %d", i++));
	LOG("update");
	try {

		// Vòng lặp mô phỏng vật lý
		float timestep = Timer::ins.getTimePassed();
		if (timestep > 1.0f)
			timestep = 1.0f;
		impl->world->update(timestep);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Physic::close() {
	LOG("close");
	try {

		// Dọn dẹp
		impl->common.destroyPhysicsWorld(impl->world);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
