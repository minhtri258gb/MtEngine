#define __MT_TERRAIN_ENV_CPP__

#include "common.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"
#include "TerrainEnv.h"

#include "engine/file/FileCFG.h"
#include "engine/file/Image.h"
#include "physic/body/RigidBody.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


class TerrainEnv::TerrainEnvImpl {
public:
	StaticTerrain* model;
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
		if (heightScale == 0.0f)
			throw error("HEIGHT_SCALE_ZERO", "Cau hinh heightScale ko hop le!");
		if (cellScale == 0.0f)
			throw error("CELL_SCALE_ZERO", "Cau hinh cellScale ko hop le!");

		// Load Data
		Image data;
		data.load(pathDir + terrainName);
		int depth = data.getWidth();
		int width = data.getHeight();

		// Convert data
		vector<float> heightData = vector(depth * width, 0.0f);
		for (int z = 0; z < width; z++) {
			for (int x = 0; x < depth; x++) {
				int index = (z*width + x);
				// Màu từ 0 - 255, Chuyển thành 0 - 1, Nhân với độ cao địa hình
				heightData[z*depth+x] = (float)data[index] / 255.0f * heightScale;
			}
		}

		// Init Model
		impl->model = new StaticTerrain();
		impl->model->initVAO(depth, width, heightData, cellScale);
		impl->model->initTexture(pathDir + textureFile);
		Graphic::ins.scene.terrainStatic = impl->model;

		// Terrain* terrain = new Terrain();
		// terrain->init(terrainName);
		// Graphic::ins.scene.terrain = terrain;

		// Init Body
		// vec3 offsetOrigin(depth/2, heightScale/2, width/2); // Căn giữa body địa hình
		// impl->body = Physic::ins.builder.createHeightField(depth, width, heightData, cellScale, offsetOrigin);
	}
	catch (Exception e) {
		track(e);
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
