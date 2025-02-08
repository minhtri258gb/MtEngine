#ifndef __MT_TEST_ENTITY_H__
#define __MT_TEST_ENTITY_H__

#include "Entity.h"
#include "graphic/models/Model.h"

namespace mt {
namespace game {

class TestEnt : public Entity {

public:

	// Constructor
	TestEnt(std::string name);
	~TestEnt();

	// Forward
	void init();
	void update();

	// Native

private:

	// Variables
	class TestEntImpl;
	TestEntImpl* impl;

};

}}

#endif
