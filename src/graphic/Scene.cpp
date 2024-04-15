#define __MT_SCENE_CPP__

#include "common.h"
#include "engine/Config.h"
#include "Scene.h"
#include "graphic/Graphic.h"

#include "graphic/other/DebugFrame.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


// DebugFrame debugFrame;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::init()
{
	float width = Config::ins.windowWidth;
	float height = Config::ins.windowHeight;

	this->proj.perspective(Math::toRadian(80.0), width/height, 0.1f, 99999.0f);
	this->view = mat4();

	Graphic::ins.shaderProgramMgr.setSceneProj(proj);
	Graphic::ins.shaderProgramMgr.setSceneView(view);

	// // Debug
	// vector<vec3> vertices;
	// vertices.push_back(vec3(-0.5f, 0.0f, -0.5f));
	// vertices.push_back(vec3( 0.5f, 0.0f, -0.5f));
	// vertices.push_back(vec3(-0.5f, 0.0f,  0.5f));
	// vertices.push_back(vec3( 0.5f, 0.0f,  0.5f));
	// vector<uint> indices;
	// indices.push_back(0); indices.push_back(2); indices.push_back(1);
	// indices.push_back(1); indices.push_back(2); indices.push_back(3);
	// debugFrame.loadVAO(vertices, indices);
}

void Scene::update()
{
	if (this->sourceMap)
		this->sourceMap->update();
	if (this->quakeMap)
		this->quakeMap->update();
	if (this->bspMap)
		this->bspMap->update();
}

void Scene::render()
{
	if (this->sky)
		this->sky->render();
	if (this->terrainStatic)
		this->terrainStatic->render();
	if (this->terrain)
		this->terrain->render();
	if (this->sourceMap)
		this->sourceMap->render();
	if (this->quakeMap)
		this->quakeMap->render();
	if (this->bspMap)
		this->bspMap->render();
	
	for (ModelRender m : this->lstModel)
	{
		if (!m.isActive)
			continue;
		vec3 pos;
		quat rot;
		vec3 scale = vec3(1,1,1);
		if (m.pos != nullptr)
			pos = *m.pos;
		if (m.rot != nullptr)
			rot = *m.rot;
		if (m.scale != nullptr)
			scale = *m.scale;
		m.model->render(pos, rot, scale);
	}

	// Debug
	// debugFrame.render(vec3(), quat(), vec3(100,100,100));
	
}
