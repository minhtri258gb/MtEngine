#define __MT_TEST_EMITTER_ENTITY_CPP__

#include <list>

#include "common.h"
#include "graphic/Graphic.h"
#include "TestEmitterEnt.h"

#include "graphic/particles/Emitter.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;
using namespace mt::game;


class TestEmitterEnt::TestEmitterEntImpl
{
public:
  // Component
	Emitter emitter;
  list<Particle*> particles;
};

TestEmitterEnt::TestEmitterEnt(string name)
{
	// Implement
	impl = new TestEmitterEntImpl();

  // Component
	impl->emitter.init(name, impl->particles);

  // Default value
  this->isAction = true;

}

TestEmitterEnt::~TestEmitterEnt()
{
  // Component
  impl->emitter.del(impl->particles);

	// Implement
	delete impl;
}

void TestEmitterEnt::update()
{
  if (!(!this->isAction && impl->particles.size() == 0))
  {
    impl->emitter.originB = this->originB;
    impl->emitter.originE = this->originE;
    impl->emitter.velocityB = this->velocityB;
    impl->emitter.velocityE = this->velocityE;
    impl->emitter.update(impl->particles, this->isAction);
  }
}

void TestEmitterEnt::render()
{
  if (impl->particles.size() > 0)
  	impl->emitter.render(impl->particles);
}
