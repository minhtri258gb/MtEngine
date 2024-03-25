#define __MT_MAP_BUILDER_CPP__

#include "common.h"
#include "MapBuilder.h"

#include "engine/file/FileCFG.h"

#include "./LobbyMap.h"

using namespace std;
using namespace mt::game;


Map* MapBuilder::load(std::string name)
{
  // Read config
	FileCFG* fCFG = new FileCFG("../res/maps/"+name+".cfg");
	
	fCFG->select("general");
	string type = fCFG->get("type");

  // Return
  return new LobbyMap(name);
}

void MapBuilder::clear(Map* pMap)
{
  delete pMap;
}
