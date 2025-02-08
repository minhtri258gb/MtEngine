#define __MT_SIMPLE_MAP_CPP__

#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "engine/Config.h"
#include "SimpleMap.h"

#include "engine/file/FileCFG.h"
#include "game/enviroments/SkyEnv.h"
#include "game/enviroments/TerrainStaticEnv.h"
#include "game/entities/TestEnt.h"
#include "game/entities/GroundEnt.h"
#include "game/entities/TestAnimEnt.h"
#include "game/entities/TestParticleEnt.h"
#include "game/entities/TestEmitterEnt.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::game;


class SimpleMap::SimpleMapImpl {
public:

	// General
	string name;

	// Enviroment
	SkyEnv* sky;
	TerrainStaticEnv* terStatic;

	// Entities
	vector<Entity*> lstEntities;
};


SimpleMap::SimpleMap(string name) {
	LOG("SimpleMap");
	try {

		// Implement
		impl = new SimpleMapImpl();
		impl->name = name;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
SimpleMap::~SimpleMap() {
	LOG("~SimpleMap");

	// Implement
	delete impl;
}

void SimpleMap::load() {
	LOG("load");
	try {

		if (!this->needLoading)
			return;

		this->needLoading = false; // or not maybe

		// Load config
		string configPath = Config::ins.map_path + impl->name + "/info.cfg";
		FileCFG fCFG(configPath);

		// Set general
		fCFG.select("general");

		// Set player position
		vec3 playerPos = fCFG.getVec3("player");
		this->player.origin = playerPos;
		this->player.init();

		// Load enviroment
		fCFG.select("enviroment");
		string skyName = fCFG.get("skybox");
		string terrainStaticName = fCFG.get("terrainStatic");
		impl->sky = new SkyEnv(skyName);
		impl->terStatic = new TerrainStaticEnv(terrainStaticName);

		// Load entities
		fCFG.select("entities");
		vector<string> lstEntCfg = fCFG.values();
		for (short i=0, sz=lstEntCfg.size(); i<sz; i++) {
			string entCfg = lstEntCfg.at(i);
			stringstream geek(entCfg);
			string entType, entName;
			geek >> entType >> entName;

			if (entType == "Test") {
				float x, y, z, rx, ry, rz, scale;
				geek >> x >> y >> z >> rx >> ry >> rz >> scale;

				TestEnt* ent = new TestEnt(entName);
				ent->pos = vec3(x, y, z);
				ent->rot = quat(Math::toRadian(rx), Math::toRadian(ry), Math::toRadian(rz));
				ent->scale = vec3(scale, scale, scale);
				ent->init();
				impl->lstEntities.push_back(ent);
			}
			else if (entType == "Ground") {
				float x, y, z, rx, ry, rz, scale;
				geek >> x >> y >> z >> rx >> ry >> rz >> scale;

				GroundEnt* ent = new GroundEnt(entName);
				ent->pos = vec3(x, y, z);
				ent->rot = quat(Math::toRadian(rx), Math::toRadian(ry), Math::toRadian(rz));
				ent->scale = vec3(scale, scale, scale);
				ent->init();
				impl->lstEntities.push_back(ent);
			}
			else if (entType == "ModelV0") {

			}
			else if (entType == "ModelV1") {

			}
			else if (entType == "Particles") {

			}
			else {

			}
		}
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void SimpleMap::update() {
	LOG("update");
	try {

		this->player.update();

		for (Entity* ent : impl->lstEntities)
			ent->update();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void SimpleMap::clear() {
	LOG("clear");
	try {

		// List Engine
		for (Entity *ent : impl->lstEntities)
			delete ent;

		impl->lstEntities.clear();

		// Sky
		if (impl->sky) {
			delete impl->sky;
			impl->sky = nullptr;
			Graphic::ins.scene.sky = nullptr;
		}

		// Terrain Static
		if (impl->terStatic != nullptr) {
			delete impl->terStatic;
			impl->terStatic = nullptr;
		}
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
