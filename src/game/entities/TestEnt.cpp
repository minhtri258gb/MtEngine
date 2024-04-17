#define __MT_TEST_ENTITY_CPP__

// #define LOG cout << __FILE__ << " | " << __LINE__ << '\n';

#include "common.h"
#include "engine/file/FileCFG.h"
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
	
	#ifdef LOG
	LOG
	#endif

	// Implement
	impl = new TestEntImpl();

	#ifdef LOG
	LOG
	#endif

	// Default
	this->name = _name;
	this->pos = vec3();
	this->rot = quat();
	this->scale = vec3(1, 1, 1);
	
	#ifdef LOG
	LOG
	#endif

}

TestEnt::~TestEnt()
{
	
	#ifdef LOG
	LOG
	#endif

	// ~Body
	if (impl->body)
	{
		impl->body->close();
		delete impl->body;
		impl->body = nullptr;
	}

	#ifdef LOG
	LOG
	#endif

	// ~Implement
	delete impl;
	
	#ifdef LOG
	LOG
	#endif

}

void TestEnt::init()
{
	
	#ifdef LOG
	LOG
	#endif

	// Model
	impl->model = Graphic::ins.modelMgr.cache(this->name);
	Graphic::ins.addModel(impl->model, &this->pos, &this->rot, &this->scale);

	#ifdef LOG
	LOG
	#endif

	// Body
	impl->body = new RigidBody();
	impl->body->create(this->name, this->pos, this->rot, this->scale);
	impl->body->action(true);
	
	#ifdef LOG
	LOG
	#endif

}

void TestEnt::update()
{
	
	#ifdef LOG
	LOG
	#endif

	// Update physic location
	impl->body->getTransForm(&this->pos, &this->rot);
	
	#ifdef LOG
	LOG
	#endif

}
