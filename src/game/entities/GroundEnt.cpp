#define __MT_GROUND_ENTITY_CPP__

// #define LOG cout << __FILE__ << " | " << __LINE__ << '\n';

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
	
	#ifdef LOG
	LOG
	#endif

	// Implement
	impl = new GroundEntImpl();

	#ifdef LOG
	LOG
	#endif

	// Default
	this->name = name;
	this->pos = vec3(0, -5, 0);
	this->rot = quat();
	this->scale = vec3(100, 100, 100);
	
	#ifdef LOG
	LOG
	#endif

}

GroundEnt::~GroundEnt()
{
	// ~Body
	if (impl->body)
	{
		impl->body->close();
		delete impl->body;
		impl->body = nullptr;
	}

	// Implement
	delete impl;
}

void GroundEnt::init()
{
	
	#ifdef LOG
	LOG
	#endif

	// Model
	impl->model = Graphic::ins.modelMgr.cache("plane");
	Graphic::ins.addModel(impl->model, &this->pos, &this->rot, &this->scale);

	#ifdef LOG
	LOG
	#endif

	// Body
	impl->body = new RigidBody();
	impl->body->create("shape/plane", this->pos, this->rot, this->scale);
	impl->body->action(true);
	
	#ifdef LOG
	LOG
	#endif

}

void GroundEnt::update()
{

}
