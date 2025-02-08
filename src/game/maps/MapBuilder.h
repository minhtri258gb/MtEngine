#ifndef __MT_MAP_BUILDER_H__
#define __MT_MAP_BUILDER_H__

#include "./Map.h"

namespace mt {
namespace game {

class MapBuilder {

public:

	// Static
	Map* firstLoad();
	Map* load(std::string name);

};

}}

#endif
