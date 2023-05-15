#define __MT_TEST_ENTITY_CPP__

#include "common.h"
// #include "engine/Engine.h"
#include "graphic/Graphic.h"
// #include "module/physic/Physic.h"
#include "TestEnt.h"

using namespace mt::graphic;
using namespace mt::game;

TestEnt::TestEnt(std::string name)
{
	this->model = Graphic::ins.modelMgr.cache("box");
}

TestEnt::~TestEnt()
{
}

void TestEnt::update()
{
}

void TestEnt::render()
{
	this->model->render();
}
