#define __MT_GROUND_ENTITY_CPP__

#include "common.h"
// #include "engine/Engine.h"
#include "graphic/Graphic.h"
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
	// Impl
	this->impl = new GroundEntImpl();

	// Default
	this->position = vec3();
}

GroundEnt::~GroundEnt()
{
	delete impl->body;
}

void GroundEnt::init()
{
	// Model
	impl->model = Graphic::ins.modelMgr.cache("plane");

	// Body
	impl->body = new RigidBody();
	impl->body->initPlane(this->position, quat(), vec3(0,1,0));
	impl->body->action(true);
}

void GroundEnt::update()
{

}

void GroundEnt::render()
{
	impl->model->position = this->position;
	// this->model->angle = quat(0,1,0); // #TODO
	impl->model->angle = quat(0,0,0,1); // #TODO
	impl->model->scale = vec3(80,80,80); // #TODO
	impl->model->render();
}
