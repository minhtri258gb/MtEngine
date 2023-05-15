#ifndef __MT_TEST_ENTITY_H__
#define __MT_TEST_ENTITY_H__

#include "Entity.h"
#include "graphic/models/Model.h"

namespace mt {
namespace game {

class TestEnt : public Entity
{

public:

	// Variable
	graphic::Model* model;

	// Forward
	TestEnt(std::string name);
	~TestEnt();
	void update();
	void render();

	// Native

};

}}

#endif
