#ifndef __MT_TEST_NAIM_ENTITY_H__
#define __MT_TEST_NAIM_ENTITY_H__

#include "Entity.h"
#include "graphic/models/animation/AnimationModel.h"

namespace mt {
namespace game {

class TestAnimEnt : public Entity
{

public:

	// Variable
	graphic::AnimationModel* model;

	// Forward
	TestAnimEnt(std::string name);
	~TestAnimEnt();
	void update();
	void render();

	// Native

};

}}

#endif
