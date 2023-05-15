#ifndef __MT_TEST_PARTICLE_ENTITY_H__
#define __MT_TEST_PARTICLE_ENTITY_H__

#include "Entity.h"

namespace mt {
namespace game {

class TestParticleEnt : public Entity
{

public:

	// Forward
	TestParticleEnt(std::string name);
	~TestParticleEnt();
	void update();
	void render();

private:

	class TestParticleEntImpl;
	TestParticleEntImpl* impl;

};

}}

#endif
