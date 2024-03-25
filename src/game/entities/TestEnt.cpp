#define __MT_TEST_ENTITY_CPP__

#include "common.h"
// #include "engine/Engine.h"
#include "graphic/Graphic.h"
// #include "module/physic/Physic.h"
#include "physic/body/RigidBody.h"
#include "TestEnt.h"

using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


class TestEnt::TestEntImpl
{
public:
	Model* model;
	RigidBody* body;
};

TestEnt::TestEnt(std::string _name)
{
	// Implement
	impl = new TestEntImpl();

	// Default
	this->name = _name;
	this->position = vec3(0,0,0);
	this->angle = quat();
	this->scale = vec3(1,1,1);
}

TestEnt::~TestEnt()
{
	// Implement
	delete impl;
}

void TestEnt::init()
{
	// Model
	impl->model = Graphic::ins.modelMgr.cache(this->name);

	// Body
	float radius = 1.0f;
	impl->body = new RigidBody();
	impl->body->initSphere(this->position, radius);
	impl->body->action(true);
}

void TestEnt::update()
{
	// Update physic location
	this->position = impl->body->getOrigin();
}

void TestEnt::render()
{
	impl->model->position = this->position;
	impl->model->angle = this->angle;
	impl->model->scale = this->scale;
	impl->model->render();
}
