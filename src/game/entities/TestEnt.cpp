#define __MT_TEST_ENTITY_CPP__

#include "common.h"
#include "engine/Log.h"
#include "engine/file/FileCFG.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"
#include "physic/body/RigidBody.h"
#include "TestEnt.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


class TestEnt::TestEntImpl {
public:
	Model* model;
	RigidBody* body;
};

TestEnt::TestEnt(string _name) {
	LOG("~TestEnt");
	try {

		// Implement
		impl = new TestEntImpl();

		// Default
		this->name = _name;
		this->pos = vec3();
		this->rot = quat();
		this->scale = vec3(1, 1, 1);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

TestEnt::~TestEnt() {
	LOG("~TestEnt");

	// ~Body
	if (impl->body) {
		impl->body->clear();
		delete impl->body;
		impl->body = nullptr;
	}

	// ~Implement
	delete impl;
}

void TestEnt::init() {
	LOG("init");
	try {

		// Model
		impl->model = Graphic::ins.modelMgr.cache(this->name);
		Graphic::ins.addModel(impl->model, &this->pos, &this->rot, &this->scale);

		// Body
		impl->body = Physic::ins.builder.load(this->name, this->pos, this->rot, this->scale);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void TestEnt::update() {
	LOG("update");
	try {

		// Update physic location
		impl->body->getTransForm(&this->pos, &this->rot);

		// cout << this->pos.y << endl;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
