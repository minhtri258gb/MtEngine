#ifndef __MT_TEST_MAP_H__
#define __MT_TEST_MAP_H__

#include "Map.h"
#include "../entities/Entity.h"

namespace mt {
namespace game {

class TestMap : public Map
{

public:

	TestMap(std::string);
	~TestMap();
	void load();
	void clear();
	void update();

private:

	// Variable
	class TestMapImpl;
	TestMapImpl* impl;

};

}}

#endif
