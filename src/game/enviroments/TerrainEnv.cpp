#define __MT_TERRAIN_ENV_CPP__

#include "common.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"
#include "TerrainEnv.h"

#include "engine/file/FileCFG.h"
#include "engine/file/Image.h"
#include "engine/random/PerlinNoise.h"
#include "graphic/terrain/TerrainInf.h"
#include "physic/body/RigidBody.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


class TerrainEnv::TerrainEnvImpl {
public:
	TerrainInf* model;
	RigidBody* body;
	string m_name;
};

TerrainEnv::TerrainEnv(string name) {
	LOG("TerrainEnv");
	try {

		// Implement
		impl = new TerrainEnvImpl();
		impl->m_name = name;
		
		// Load config
		string pathDir = "./res/terrains/" + name + "/";
		FileCFG fCFG(pathDir + "info.cfg");
		fCFG.select("terrain");
		string terrainName = fCFG.get("heightmap");
		string textureFile = fCFG.get("texture");
		float heightScale = fCFG.getFloat("heightScale");
		float cellScale = fCFG.getFloat("cellScale");

		// Validate
		if (terrainName != "noise")
			throw error("HEIGHTMAP_TYPE_INVAIL", "TerrainInf chi dung heightmap noise!");
		if (cellScale == 0.0f)
			throw error("CELL_SCALE_ZERO", "Cau hinh cellScale ko hop le!");

		fCFG.select("noise");
		int depth = fCFG.getInt("depth");
		int width = fCFG.getInt("width");

		PerlinNoise noise;
		noise.setPersistence(fCFG.getFloat("persistence"));
		noise.setFrequency(fCFG.getFloat("frequency"));
		noise.setAmplitude(fCFG.getFloat("amplitude"));
		noise.setOctaves(fCFG.getFloat("octaves"));
		noise.setSeed(fCFG.getInt("seed"));

		// Load Data
		HeightmapData hmData;
		hmData.loadNoise(noise, depth, width, heightScale);

		// Init Model
		impl->model = new TerrainInf();
		impl->model->initVAO(&hmData);
		impl->model->initTexture(pathDir + textureFile);
		Graphic::ins.scene.terrain = impl->model;

		// Init Body
		impl->body = Physic::ins.builder.createHeightField(&hmData, cellScale);
	}
	catch (Exception e) {
		track(e);
		if (e.getCode() == "LOAD_FAIL")
			e.setMessage("CONFIG_NOT_FOUND", "Khong tim thay file Config TerrainInf (res/terrains/"+name+"/info.cfg)");
		throw e;
	}
}
TerrainEnv::~TerrainEnv() {
	LOG("~TerrainEnv");

	// ~Model
	if (impl->model) {
		impl->model->clear();
		delete impl->model;
		impl->model = nullptr;
		Graphic::ins.scene.terrainStatic = nullptr;
	}

	// ~Body
	if (impl->body) {
		impl->body->clear();
		delete impl->body;
		impl->body = nullptr;
	}

	// ~Implement
	delete impl;
}

void TerrainEnv::update() {
	LOG("update");
	try {

		// Update physic location
		// impl->body->getTransForm(&this->pos, &this->rot);

		// cout << this->pos.y << endl;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
