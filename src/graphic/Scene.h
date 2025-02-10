#ifndef __MT_SCENE_H__
#define __MT_SCENE_H__

#include "graphic/sky/SkyBox.h"
#include "graphic/terrain/TerrainStatic.h"
#include "graphic/terrain/TerrainInf.h"
#include "graphic/bsp/BspSourceMap.h"
#include "graphic/bsp/BspQuakeMap.h"
#include "graphic/bsp/BspMap.h"
#include "graphic/models/Model.h"

namespace mt {
namespace graphic {

struct ModelRender {
	Model* model;
	vec3* pos;
	quat* rot;
	vec3* scale;
	bool isActive;

	ModelRender(Model* _model, vec3* _pos, quat* _rot, vec3* _scale) {
		model = _model;
		pos = _pos;
		rot = _rot;
		scale = _scale;
		isActive = true;
	}
};

class Scene {

public:

	// Variable
	mat4 proj;
	mat4 view;

	// Enviroment
	SkyBox* sky;
	TerrainStatic* terrainStatic;
	TerrainInf* terrain;
	BspSourceMap* sourceMap;
	BspQuakeMap* quakeMap;
	BspMap* bspMap;

	std::vector<ModelRender> lstModel;

	// Forward
	Scene();
	~Scene();

	void init();
	void update();
	void render();

	// Native

};

}}

#endif
