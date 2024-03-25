#ifndef __MT_TEST_EMITTER_ENTITY_H__
#define __MT_TEST_EMITTER_ENTITY_H__

#include "Entity.h"

namespace mt {
namespace game {

class TestEmitterEnt : public Entity
{

public:

	// Properties
  vec3 originB, originE, velocityB, velocityE;
	bool isAction;

	// Forward
	TestEmitterEnt(std::string name);
	~TestEmitterEnt();
	void update();
	void render();

private:

	class TestEmitterEntImpl;
	TestEmitterEntImpl* impl;

};

}}

#endif
