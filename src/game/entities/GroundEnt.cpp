#define __MT_GROUND_ENTITY_CPP__

#include "common.h"
// #include "engine/Engine.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"
#include "physic/body/RigidBody.h"
#include "GroundEnt.h"

using namespace std;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


class GroundEnt::GroundEntImpl {
public:
	Model* model;
	RigidBody* body;
};

GroundEnt::GroundEnt(string name) {
	try {

		// Implement
		impl = new GroundEntImpl();

		// Default
		this->name = name;
		this->pos = vec3(0, -5, 0);
		this->rot = quat();
		this->scale = vec3(100, 100, 100);

	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

GroundEnt::~GroundEnt() {

	// ~Body
	if (impl->body) {
		impl->body->clear();
		delete impl->body;
		impl->body = nullptr;
	}

	// Implement
	delete impl;
}

void GroundEnt::init() {
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

void GroundEnt::update() {
	try {

		// Update physic location
		// impl->body->getTransForm(&this->pos, &this->rot);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
