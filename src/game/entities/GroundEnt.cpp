#define __MT_GROUND_ENTITY_CPP__

#include "common.h"
// #include "engine/Engine.h"
#include "graphic/Graphic.h"
// #include "module/physic/Physic.h"
#include "GroundEnt.h"

using namespace std;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;

GroundEnt::GroundEnt(string name)
{
	model = Graphic::ins.modelMgr.cache("plane");

	body = new RigidBody();
	body->initPlane();
	body->action(true);
}

GroundEnt::~GroundEnt()
{
	delete body;
}

void GroundEnt::update()
{
}

void GroundEnt::render()
{
	this->model->position = this->position;
	this->model->angle = quat(0,0,0,1); // #TODO
	this->model->scale = vec3(80,80,80); // #TODO
	this->model->render();
}
