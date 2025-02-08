#define __MT_TERRAIN_STATIC_ENV_CPP__

#include "common.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"
#include "TerrainStaticEnv.h"

#include "engine/file/FileCFG.h"
#include "engine/file/Image.h"
#include "engine/random/PerlinNoise.cpp"
#include "physic/body/RigidBody.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


class TerrainStaticEnv::TerrainStaticEnvImpl {
public:
	StaticTerrain* model;
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

		int depth = 0;
		int width = 0;
		vector<float> heightData;
		vec3 offsetOrigin; // Căn giữa body địa hình

		if (terrainName == "noise") {
			fCFG.select("noise");
			depth = fCFG.getInt("depth");
			width = fCFG.getInt("width");

			PerlinNoise noise;
			noise.setPersistence(fCFG.getFloat("persistence"));
			noise.setFrequency(fCFG.getFloat("frequency"));
			noise.setAmplitude(fCFG.getFloat("amplitude"));
			noise.setOctaves(fCFG.getFloat("octaves"));
			noise.setSeed(fCFG.getInt("seed"));

			// Convert data
			heightData = vector(depth * width, 0.0f);
			float minH, maxH;
			for (int z = 0; z < width; z++) {
				for (int x = 0; x < depth; x++) {
					float height = (float)(noise.calHeight(x, z) + noise.getAmplitude());
					minH = min(minH, height);
					maxH = max(maxH, height);
					heightData[z*depth+x] = height;
				}
			}

			// Offset Origin
			offsetOrigin = vec3(depth/2, maxH - (maxH-minH)/2, width/2); // Căn giữa body địa hình
		}
		else {

			// Validate
			float heightScale = fCFG.getFloat("heightScale");
			if (heightScale == 0.0f)
				throw error("HEIGHT_SCALE_ZERO", "Cau hinh heightScale ko hop le!");

			// Load Data
			Image data;
			data.load(pathDir + terrainName);
			depth = data.getWidth();
			width = data.getHeight();

			// Convert data
			heightData = vector(depth * width, 0.0f);
			for (int z = 0; z < width; z++) {
				for (int x = 0; x < depth; x++) {
					int index = (z*width + x);
					// Màu từ 0 - 255, Chuyển thành 0 - 1, Nhân với độ cao địa hình
					heightData[z*depth+x] = (float)data[index] / 255.0f * heightScale;
				}
			}

			// Offset Origin
			offsetOrigin = vec3(depth/2, heightScale/2, width/2); // Căn giữa body địa hình
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
		impl->model = new StaticTerrain();
		impl->model->initVAO(depth, width, heightData, cellScale);
		impl->model->initTexture(pathDir + textureFile);
		Graphic::ins.scene.terrainStatic = impl->model;

		// Init Body
		impl->body = Physic::ins.builder.createHeightField(depth, width, heightData, cellScale, offsetOrigin);
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
