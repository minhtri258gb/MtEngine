#ifndef __MT_AREA_BOUND_MAP_H__
#define __MT_AREA_BOUND_MAP_H__

#include "Map.h"
#include "../entities/Entity.h"

namespace mt {
namespace game {

class AreaBoundMap : public Map {

public:

	// Method
	AreaBoundMap(std::string);
	~AreaBoundMap();

	void load();
	void update();
	void render();
	void clear();

private:

	// Variable
	class AreaBoundMapImpl;
	AreaBoundMapImpl* impl;

};

}}

#endif
