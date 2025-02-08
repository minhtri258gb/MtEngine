#ifndef __MT_AREA_MAP_H__
#define __MT_AREA_MAP_H__

#include "Map.h"
#include "../entities/Entity.h"

namespace mt {
namespace game {

class AreaMap : public Map {

public:

	// Method
	AreaMap(std::string);
	~AreaMap();

	void load();
	void update();
	void render();
	void clear();

private:

	// Variable
	class AreaMapImpl;
	AreaMapImpl* impl;

};

}}

#endif
