#define __MT_MAP_BUILDER_CPP__

#include "common.h"

#include "engine/Config.h"
#include "engine/file/FileCFG.h"
#include "engine/exception/LoadException.h"

#include "MapBuilder.h"

#include "TestMap.h"
#include "LobbyMap.h"
#include "AreaBoundMap.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::game;


Map* MapBuilder::firstLoad()
{
	try {
		string mapName = "lobby"; // lobby is default

		// Tải file state.ini
		FileCFG* fCFG = nullptr;

		try
		{
			fCFG = new FileCFG(Config::ins.system_path + "state.cfg");
			fCFG->select("last");
			mapName = fCFG->get("map");
		}
		catch (LoadException e)
		{
			// Nếu chưa có file thì tạo file với state mặc định
			delete fCFG;
			fCFG = new FileCFG();
			fCFG->addSession("last");
			fCFG->set("map", mapName);
			fCFG->save(Config::ins.system_path + "state.cfg");
		}
		
		// Return
		delete fCFG;
		return MapBuilder::load(mapName);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

Map* MapBuilder::load(string mapName)
{
	try {

		// Read type of map
		string configPath = Config::ins.map_path + mapName + ".cfg";
		FileCFG* fCFG = new FileCFG(configPath);
		fCFG->select("general");
		string type = fCFG->get("type");
		delete fCFG;

		// Load map
		Map* map = nullptr;
		if (type == "test")
			map = new TestMap(mapName);
		else if (type == "lobby")
			map = new LobbyMap(mapName);
		else if (type == "area_bound")
			map = new AreaBoundMap(mapName);

		// Return
		return map;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void MapBuilder::clear(Map* pMap) {
	delete pMap;
}
