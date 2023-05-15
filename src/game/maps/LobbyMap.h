#ifndef __MT_LOBBY_MAP_H__
#define __MT_LOBBY_MAP_H__

#include "Map.h"
#include "../entities/Entity.h"
// #include "../enviroment/terrain/Terrain.h"
// #include "../enviroment/PhysicDebug.h"

namespace mt {
namespace game {

class LobbyMap : public Map
{

public:

	// Variable
	// PhysicDebug* physicDebug;
	// Terrain* terrain;
	std::vector<Entity*> lstEntitiesStatic;
	// std::vector<Entity*> lstEntitiesDynamic;

	// Forward
	LobbyMap();
	~LobbyMap();
	void load();
	void clear();
	void update();
	void render();

private:

	// Variable
	class LobbyMapImpl;
	LobbyMapImpl* impl;

};

}}

#endif
