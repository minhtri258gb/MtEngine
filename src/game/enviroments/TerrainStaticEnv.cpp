#define __MT_TERRAIN_STATIC_ENV_CPP__

#include "common.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"
#include "TerrainStaticEnv.h"

#include "engine/file/FileCFG.h"
#include "engine/data/HeightmapData.h"
#include "physic/body/RigidBody.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


class TerrainStaticEnv::TerrainStaticEnvImpl {
public:
	HeightmapData data;
	TerrainStatic* model;
	RigidBody* body;
	string m_name;
};

TerrainStaticEnv::TerrainStaticEnv(string name) {
	LOG("TerrainStaticEnv");
	try {

		// Implement
		impl = new TerrainStaticEnvImpl();
		impl->m_name = name;
		
		// Load config
		string pathDir = "./res/terrains/" + name + "/";
		FileCFG fCFG(pathDir + "info.cfg");
		fCFG.select("terrain");
		string terrainName = fCFG.get("heightmap");
		string textureFile = fCFG.get("texture");
		float cellScale = fCFG.getFloat("cellScale");

		// Validate
		if (cellScale == 0.0f)
			throw error("CELL_SCALE_ZERO", "Cau hinh cellScale ko hop le!");

		// Load Heightmap Map
		HeightmapData hmData;
		if (terrainName == "noise") {
			fCFG.select("noise");

			PerlinNoise noise;
			noise.setPersistence(fCFG.getFloat("persistence"));
			noise.setFrequency(fCFG.getFloat("frequency"));
			noise.setAmplitude(fCFG.getFloat("amplitude"));
			noise.setOctaves(fCFG.getFloat("octaves"));
			noise.setSeed(fCFG.getInt("seed"));

			// Load Data
			int depth = fCFG.getInt("depth");
			int width = fCFG.getInt("width");
			hmData.loadNoise(noise, depth, width, 1.0f);
		}
		else {

			// Validate
			float heightScale = fCFG.getFloat("heightScale");
			if (heightScale == 0.0f)
				throw error("HEIGHT_SCALE_ZERO", "Cau hinh heightScale ko hop le!");

			// Load Data
			hmData.loadImage(pathDir + terrainName, heightScale);
		}
		// {
		// 	BTFile *filebt = new BTFile("res/terrain/" + terrainName + "/heightmap.bt");
		// 	float depth = filebt->getRows();
		// 	float width = filebt->getColumns();

		// 	vector<float> heightmapData;
		// 	heightmapData.resize((float)(depth * width), 0.0f);
		// 	unsigned char* pixelPtr = data.getDataPtr();
		// 	for (auto i = 0; i < width; i++)
		// 		for (auto j = 0; j < depth; j++)
		// 		{
		// 			heightmapData[i*depth+j] = float(*pixelPtr) / 255.0f;
		// 			pixelPtr += data.getChannel();
		// 		}
		// }

		// Init Model
		impl->model = new TerrainStatic();
		impl->model->initVAO(&hmData, cellScale);
		impl->model->initTexture(pathDir + textureFile);
		Graphic::ins.scene.terrainStatic = impl->model;

		// Init Body
		impl->body = Physic::ins.builder.createHeightField(&hmData, cellScale);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
TerrainStaticEnv::~TerrainStaticEnv() {
	LOG("~TerrainStaticEnv");

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

void TerrainStaticEnv::update() {
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
