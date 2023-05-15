#define __MT_TEST_ANIM_ENTITY_CPP__

#include "common.h"
// #include "engine/Engine.h"
#include "graphic/Graphic.h"
// #include "module/physic/Physic.h"
#include "TestAnimEnt.h"

using namespace mt::graphic;
using namespace mt::game;

TestAnimEnt::TestAnimEnt(std::string name)
{
	// this->model = dynamic_cast<AnimationModel*>(Graphic::ins.modelMgr.cache("box"));
	this->model = new AnimationModel();
}

TestAnimEnt::~TestAnimEnt()
{
	delete this->model;
}

void TestAnimEnt::update()
{
	this->model->update();
}

void TestAnimEnt::render()
{
	this->model->render();
}
