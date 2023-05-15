#define __MT_TEST_PARTICLE_ENTITY_CPP__

#include "common.h"
// #include "engine/Engine.h"
#include "graphic/Graphic.h"
// #include "module/physic/Physic.h"
#include "TestParticleEnt.h"

#include "graphic/particles/Sprite.h"

using namespace mt::graphic;
using namespace mt::game;

class TestParticleEnt::TestParticleEntImpl
{
public:
	Sprite sprite;
};

TestParticleEnt::TestParticleEnt(std::string name)
{
	// Implement
	this->impl = new TestParticleEntImpl();

	this->impl->sprite.load("mai");
}

TestParticleEnt::~TestParticleEnt()
{
	// Implement
	delete this->impl;
}

void TestParticleEnt::update()
{
}

void TestParticleEnt::render()
{
	this->impl->sprite.render();
}
