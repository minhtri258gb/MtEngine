#ifndef __MT_SIMPLE_MAP_H__
#define __MT_SIMPLE_MAP_H__

#include "Map.h"
#include "game/entities/Entity.h"

namespace mt {
namespace game {

class SimpleMap : public Map {

public:

	// Method
	SimpleMap(std::string);
	~SimpleMap();

	void load();
	void update();
	void clear();

private:

	// Variable
	class SimpleMapImpl;
	SimpleMapImpl* impl;

};

}}

#endif
