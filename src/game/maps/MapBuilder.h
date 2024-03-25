#ifndef __MT_MAP_BUILDER_H__
#define __MT_MAP_BUILDER_H__

#include "./Map.h"

namespace mt {
namespace game {

class MapBuilder
{

public:

	// Static
  static Map* load(std::string name);
  static void clear(Map* pMap);

};

}}

#endif
