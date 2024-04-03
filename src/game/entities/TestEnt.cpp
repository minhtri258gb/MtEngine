#define __MT_TEST_ENTITY_CPP__

#include "common.h"
// #include "engine/Engine.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"
#include "physic/body/RigidBody.h"
#include "TestEnt.h"

using namespace std;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


class TestEnt::TestEntImpl
{
public:
	Model* model;
	RigidBody* body;
};

TestEnt::TestEnt(string _name)
{
	// Implement
	impl = new TestEntImpl();

	// Default
	this->name = _name;
	this->pos = vec3();
	this->rot = quat();
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
	Graphic::ins.addModel(impl->model, &this->pos, &this->rot, &this->scale);

	// Body
	impl->body = Physic::ins.createBox(this->pos, this->rot, this->scale, 1);
	Physic::ins.add(impl->body);
}

void TestEnt::update()
{
	// Update physic location
	impl->body->getTransForm(&this->pos, &this->rot);
}
