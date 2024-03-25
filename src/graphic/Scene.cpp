#define __MT_SCENE_CPP__

#include "common.h"
#include "engine/Config.h"
#include "Scene.h"
#include "Graphic.h"

using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;

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
}
