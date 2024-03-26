#ifndef __MT_AREA_BOUND_MAP_H__
#define __MT_AREA_BOUND_MAP_H__

#include "Map.h"
#include "../entities/Entity.h"

namespace mt {
namespace game {

class AreaBoundMap : public Map
{

public:

	AreaBoundMap(std::string);
	~AreaBoundMap();
	void load();
	void clear();
	void update();
	void render();

private:

	// Variable
	class AreaBoundMapImpl;
	AreaBoundMapImpl* impl;

};

}}

#endif
