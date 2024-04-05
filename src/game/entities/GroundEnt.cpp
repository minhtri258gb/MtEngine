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


class GroundEnt::GroundEntImpl
{
public:
	Model* model;
	RigidBody* body;
};

GroundEnt::GroundEnt(string name)
{
	// Implement
	impl = new GroundEntImpl();

	// Default
	this->name = name;
	this->pos = vec3(0, -5, 0);
	this->rot = quat();
	this->scale = vec3(100, 100, 100);
}

GroundEnt::~GroundEnt()
{
	Physic::ins.remove(impl->body);

	// Implement
	delete impl;
}

void GroundEnt::init()
{
	// Model
	impl->model = Graphic::ins.modelMgr.cache("plane");
	Graphic::ins.addModel(impl->model, &this->pos, &this->rot, &this->scale);

	// Body
	impl->body = Physic::ins.create("shape/plane", this->pos, this->rot, this->scale);
	Physic::ins.add(impl->body);
}

void GroundEnt::update()
{

}
