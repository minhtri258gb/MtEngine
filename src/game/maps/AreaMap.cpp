#define __MT_AREA_MAP_CPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "AreaMap.h"

#include "engine/file/FileCFG.h"
#include "graphic/sky/SkyBox.h"
#include "graphic/terrain/StaticTerrain.h"
#include "graphic/terrain/Terrain.h"
#include "graphic/bsp/BspSourceMap.h"
#include "graphic/bsp/BspQuakeMap.h"
#include "graphic/bsp/BspMap.h"
#include "game/entities/TestEnt.h"
#include "game/entities/GroundEnt.h"
#include "game/entities/TestAnimEnt.h"
#include "game/entities/TestParticleEnt.h"
#include "game/entities/TestEmitterEnt.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::game;


class AreaMap::AreaMapImpl {
public:

	// General
	string name;
	int size;
	vec3 playerPos = vec3();

	// Enviroment
	string skyName;
	SkyBox* sky;
	string terrainName;
	StaticTerrain* terrainStatic;
	Terrain* terrain;
	BspSourceMap* sourceMap;
	BspQuakeMap* quakeMap;
	BspMap* bspMap;

	// Entities
	vector<Entity*> lstEntities;
};

AreaMap::AreaMap(string name) {
	try {

		// Implement
		impl = new AreaMapImpl();
		impl->name = name;

		// Load config
		string configPath = Config::ins.map_path + name + "/info.cfg";
		FileCFG* fCFG = new FileCFG(configPath);

		// Set general
		fCFG->select("general");
		impl->size = fCFG->getInt("size");
		impl->playerPos = fCFG->getVec3("player_posotion");

		// Set enviroment
		fCFG->select("enviroment");
		impl->skyName = fCFG->get("skybox");
		impl->terrainName = fCFG->get("terrain");

		delete fCFG;
	}
	catch (Exception e) {
		if (e.getCode() == "SESSION_NOT_FOUND") {
			throw error("MAP_CONFIG_INVAIL", "AreaMap ("+name+") phai co session \"enviroment\"!");
		}
		else {
			track(e);
			throw e;
		}
	}
}

AreaMap::~AreaMap() {
	// // Xoa debug physic
	// if (this->physicDebug)
	// 	delete this->physicDebug;

	// // Xoa terrain
	// if (this->terrain)
	// 	delete this->terrain;

	// // Xoa entity tinh
	// for (Entity* ent : this->lstEntitiesStatic)
	// 	delete ent;
	// this->lstEntitiesStatic.clear();

	// // Xoa entity tinh
	// for (Entity* ent : this->lstEntitiesDynamic)
	// 	delete ent;
	// this->lstEntitiesDynamic.clear();

	// // Clean physic
	// if (this->world) {
	// 	newton::NewtonDestroyAllBodies(this->world);
	// 	newton::NewtonDestroy(this->world);
	// }

	// Implement
	delete impl;
}

void AreaMap::load() {
	try {

		if (!this->needLoading)
			return;

		this->needLoading = false; // or not maybe

		// Data config
		// string pathDir = "./res/terrains/static/lobby/";
		// FileCFG* fCFG = new FileCFG(pathDir + "info.cfg");

		// fCFG->select("general");
		// string terrainName = fCFG->get("type");
		// unsigned int size = fCFG->getUInt("size");

		// =================== Sky ===================
		impl->sky = new SkyBox();
		impl->sky->init(impl->skyName);
		Graphic::ins.scene.sky = impl->sky;

		// =================== Terrain Static ===================
		// impl->terrainStatic = new StaticTerrain();
		// impl->terrainStatic->init(impl->terrainName);
		// Graphic::ins.scene.terrainStatic = impl->terrainStatic;

		// =================== Terrain QuadTree ===================
		// impl->terrain = new Terrain();
		// impl->terrain->init("something");

		// =================== BSP Source Map ===================
		// impl->sourceMap = new BspSourceMap();
		// impl->sourceMap->init("de_dust2");

		// =================== BSP Quake Map ===================
		// impl->quakeMap = new BspQuakeMap();
		// impl->quakeMap->init("de_dust2");

		// =================== BSP Map ===================
		// impl->bspMap = new BspMap();
		// impl->bspMap->init("de_dust2");

		// =================== Ent Ground ===================
		// GroundEnt* groundEnt = new GroundEnt("matdat");
		// groundEnt->position = vec3(0,-5,0);
		// groundEnt->init();
		// this->lstEntitiesStatic.push_back(groundEnt);

		// =================== Ent Box ===================
		// TestEnt* boxEnt1 = new TestEnt("box");
		// boxEnt1->position = vec3(0,50,-2);
		// boxEnt1->scale = vec3(1,1,1);
		// boxEnt1->init();
		// this->lstEntitiesStatic.push_back(boxEnt1);

		// =================== Ent Box ===================
		// TestEnt* boxEnt2 = new TestEnt("box");
		// boxEnt2->position = vec3(128.0, 0.0, 0.0);
		// this->lstEntitiesStatic.push_back(boxEnt2);

		// =================== Ent Box ===================
		// TestEnt* boxEnt3 = new TestEnt("box");
		// boxEnt3->position = vec3(0.0, 0.0, 128.0);
		// this->lstEntitiesStatic.push_back(boxEnt3);

		// =================== Ent Box ===================
		// TestEnt* boxEnt4 = new TestEnt("box");
		// boxEnt4->position = vec3(128.0, 0.0, 128.0);
		// this->lstEntitiesStatic.push_back(boxEnt4);

		// Image data;
		// data.load(pathDir + terrainName);
		// // BTFile *filebt = new BTFile("res/terrain/" + terrainName + "/heightmap.bt");

		// // Create world physic
		// this->world = newton::NewtonCreate();

		// // Debug Physic
		// this->physicDebug = new PhysicDebug();
		// this->physicDebug->init();

		// Enviroment
		// this->terrain = new Terrain();
		// this->terrain->position = vec3(-16.0f, -4.0f, -16.0f);
		// this->terrain->size = vec3(32.0f, 4.0f, 32.0f);
		// this->terrain->init();

		// // Tao mat dat
		// PlaneEnt* ground = new PlaneEnt();
		// ground->position = vec3();
		// ground->size = vec2(32.0f, 32.0f);
		// ground->color = vec4i(200, 200, 200, 255);
		// ground->initBody(false);
		// this->lstEntitiesStatic.push_back(ground);

		// // Tao buc tuong
		// BlockEnt* wall1 = new BlockEnt();
		// wall1->position = vec3(-16.0f, 2.5f, 0.0f);
		// wall1->size = vec3(1.0f, 5.0f, 32.0f);
		// wall1->color = vec4i(0, 121, 241, 255);
		// wall1->wireframe = false;
		// wall1->initBody(false);
		// this->lstEntitiesStatic.push_back(wall1);

		// BlockEnt* wall2 = new BlockEnt();
		// wall2->position = vec3(16.0f, 2.5f, 0.0f);
		// wall2->size = vec3(1.0f, 5.0f, 32.0f);
		// wall2->color = vec4i(0, 158, 47, 255);
		// wall2->wireframe = false;
		// wall2->initBody(false);
		// this->lstEntitiesStatic.push_back(wall2);

		// BlockEnt* wall3 = new BlockEnt();
		// wall3->position = vec3(0.0f, 2.5f, 16.0f);
		// wall3->size = vec3(32.0f, 5.0f, 1.0f);
		// wall3->color = vec4i(255, 203, 0, 255);
		// wall3->wireframe = false;
		// wall3->initBody(false);
		// this->lstEntitiesStatic.push_back(wall3);

		// Tao vai thu gi do
		// int numEntitiesStatic = 30;
		// for (int i=0; i<numEntitiesStatic; i++)
		// {
		// 	BlockEnt* ent = new BlockEnt();
		// 	ent->size = vec3(		2.0f,
		// 							(float)RandomNumber::rand(1,12),
		// 							2.0f);
		// 	ent->position = vec3(	(float)RandomNumber::rand(-15, 15),
		// 							ent->size.y/2.0f,
		// 							(float)RandomNumber::rand(-15, 15));
		// 	ent->color = vec4i(		(ubyte)RandomNumber::rand(20, 255),
		// 							(ubyte)RandomNumber::rand(10, 55),
		// 							30,
		// 							255);
		// 	ent->wireframe = true;
		// 	ent->initBody(false);
		// 	this->lstEntitiesStatic.push_back(ent);
		// }

		// Tao entity dynamic
		// int numEntitiesDynamic = 10;
		// for (int i=0; i<numEntitiesDynamic; i++)
		// {
		// 	BlockEnt* cubeDynamic = new BlockEnt();
		// 	cubeDynamic->position = vec3(	(float)RandomNumber::rand(-15, 15),
		// 									20.0f,
		// 									(float)RandomNumber::rand(-15, 15));
		// 	cubeDynamic->size = vec3(1.0f, 1.0f, 1.0f);
		// 	cubeDynamic->color = vec4i(0, 0, 0, 255);
		// 	cubeDynamic->wireframe = false;
		// 	cubeDynamic->initBody(true); // ?
		// 	this->lstEntitiesDynamic.push_back(cubeDynamic);
		// }

		// Tao hinh cau
		// SphereEnt* sphereEnt = new SphereEnt(); // thieu class
		// sphereEnt->position = vec3(0, 100, 0);
		// sphereEnt->radius = 1.0f;
		// sphereEnt->color = vec4i(0, 0, 0, 255);
		// sphereEnt->initBody(true);
		// this->lstEntitiesDynamic.push_back(sphereEnt);

		// Test Entity
		// this->lstEntitiesStatic.push_back(new TestEnt("test")); // ko hien

		// this->lstEntitiesDynamic.push_back(new TestAnimEnt("asd")); // Test animation model // ok
		// this->lstEntitiesStatic.push_back(new TestParticleEnt("test")); // ok

		// Ground
		// GroundEnt* ground1 = new GroundEnt("matdat");
		// ground1->position = vec3(0,-0.5,0);
		// this->lstEntitiesStatic.push_back(ground1);
		// GroundEnt* ground2 = new GroundEnt("matdat");
		// ground2->position = vec3(256,-0.5,0);
		// this->lstEntitiesStatic.push_back(ground2);
		// GroundEnt* ground3 = new GroundEnt("matdat");
		// ground3->position = vec3(0,-0.5,256);
		// this->lstEntitiesStatic.push_back(ground3);
		// GroundEnt* ground4 = new GroundEnt("matdat");
		// ground4->position = vec3(256,-0.5,256);
		// this->lstEntitiesStatic.push_back(ground4);

		// =================== Entity kim tu thap voi normal
		// SimpleModel* kttMdl = (SimpleModel*) Graphic::ins.modelMgr.getModel("kim_tu_thap");
		// if (kttMdl == nullptr) {
		// 	kttMdl = new SimpleModel();

		// 	vector<vec3> vertices;
		// 	vertices.push_back(vec3(-0.5f,  0.0f,  0.5f));
		// 	vertices.push_back(vec3(-0.5f,  0.0f, -0.5f));
		// 	vertices.push_back(vec3( 0.5f,  0.0f, -0.5f));
		// 	vertices.push_back(vec3( 0.5f,  0.0f,  0.5f));
		// 	vertices.push_back(vec3(-0.5f,  0.0f,  0.5f));
		// 	vertices.push_back(vec3(-0.5f,  0.0f, -0.5f));
		// 	vertices.push_back(vec3( 0.0f,  0.8f,  0.0f));
		// 	vertices.push_back(vec3(-0.5f,  0.0f, -0.5f));
		// 	vertices.push_back(vec3( 0.5f,  0.0f, -0.5f));
		// 	vertices.push_back(vec3( 0.0f,  0.8f,  0.0f));
		// 	vertices.push_back(vec3( 0.5f,  0.0f, -0.5f));
		// 	vertices.push_back(vec3( 0.5f,  0.0f,  0.5f));
		// 	vertices.push_back(vec3( 0.0f,  0.8f,  0.0f));
		// 	vertices.push_back(vec3( 0.5f,  0.0f,  0.5f));
		// 	vertices.push_back(vec3(-0.5f,  0.0f,  0.5f));
		// 	vertices.push_back(vec3( 0.0f,  0.8f,  0.0f));

		// 	vector<vec2> texcoords;
		// 	texcoords.push_back(vec2(0.0f, 0.0f));
		// 	texcoords.push_back(vec2(0.0f, 5.0f));
		// 	texcoords.push_back(vec2(5.0f, 5.0f));
		// 	texcoords.push_back(vec2(5.0f, 0.0f));
		// 	texcoords.push_back(vec2(0.0f, 0.0f));
		// 	texcoords.push_back(vec2(5.0f, 0.0f));
		// 	texcoords.push_back(vec2(2.5f, 5.0f));
		// 	texcoords.push_back(vec2(5.0f, 0.0f));
		// 	texcoords.push_back(vec2(0.0f, 0.0f));
		// 	texcoords.push_back(vec2(2.5f, 5.0f));
		// 	texcoords.push_back(vec2(0.0f, 0.0f));
		// 	texcoords.push_back(vec2(5.0f, 0.0f));
		// 	texcoords.push_back(vec2(2.5f, 5.0f));
		// 	texcoords.push_back(vec2(5.0f, 0.0f));
		// 	texcoords.push_back(vec2(0.0f, 0.0f));
		// 	texcoords.push_back(vec2(2.5f, 5.0f));

		// 	vector<vec3> normals;
		// 	normals.push_back(vec3(0.0f, -1.0f, 0.0f));
		// 	normals.push_back(vec3(0.0f, -1.0f, 0.0f));
		// 	normals.push_back(vec3(0.0f, -1.0f, 0.0f));
		// 	normals.push_back(vec3(0.0f, -1.0f, 0.0f));
		// 	normals.push_back(vec3(-0.8f, 0.5f, 0.0f));
		// 	normals.push_back(vec3(-0.8f, 0.5f, 0.0f));
		// 	normals.push_back(vec3(-0.8f, 0.5f, 0.0f));
		// 	normals.push_back(vec3(0.0f, 0.5f, -0.8f));
		// 	normals.push_back(vec3(0.0f, 0.5f, -0.8f));
		// 	normals.push_back(vec3(0.0f, 0.5f, -0.8f));
		// 	normals.push_back(vec3(0.8f, 0.5f, 0.8f));
		// 	normals.push_back(vec3(0.8f, 0.5f, 0.8f));
		// 	normals.push_back(vec3(0.8f, 0.5f, 0.8f));
		// 	normals.push_back(vec3(0.0f, 0.5f, 0.8f));
		// 	normals.push_back(vec3(0.0f, 0.5f, 0.8f));
		// 	normals.push_back(vec3(0.0f, 0.5f, 0.8f));

		// 	vector<unsigned int> indices;
		// 	indices.push_back( 0); indices.push_back( 1); indices.push_back( 2); // bottom
		// 	indices.push_back( 0); indices.push_back( 2); indices.push_back( 3); // Bottom
		// 	indices.push_back( 4); indices.push_back( 6); indices.push_back( 5); // left
		// 	indices.push_back( 7); indices.push_back( 9); indices.push_back( 8); // Behide
		// 	indices.push_back(10); indices.push_back(12); indices.push_back(11); // Right
		// 	indices.push_back(13); indices.push_back(15); indices.push_back(14); // Front

		// 	kttMdl->loadVAO(vertices, texcoords, normals, indices);
		// 	kttMdl->loadTexture("./res/textures/wall.jpg");

		// 	Graphic::ins.modelMgr.addModel("kim_tu_thap", kttMdl);
		// }

		// TestEnt* ent001 = new TestEnt("kim_tu_thap");
		// ent001->position = vec3(0,0,0);
		// ent001->scale = vec3(100,100,100);
		// this->lstEntitiesStatic.push_back(ent001);

		// =================== Emitter
		// TestEmitterEnt* ent002 = new TestEmitterEnt("exp03");
		// ent002->originB = vec3(0, 0, 0);
		// ent002->originE = vec3(0, 0, 0);
		// ent002->velocityB = vec3(-1, 3, -1);
		// ent002->velocityE = vec3(1, 3, 1);
		// this->lstEntitiesDynamic.push_back(ent002);

		// HUD - Text
		// #TODO

		// Set player position
		Graphic::ins.camera.position = impl->playerPos;

		// #EXTRA
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void AreaMap::clear()
{
	for (Entity *ent : impl->lstEntities)
		delete ent;
	impl->lstEntities.clear();

	// Sky
	if (impl->sky)
	{
		delete impl->sky;
		impl->sky = nullptr;
		Graphic::ins.scene.sky = nullptr;
	}

	// Terrain Static
	if (impl->terrainStatic)
	{
		delete impl->terrainStatic;
		impl->terrainStatic = nullptr;
		Graphic::ins.scene.terrainStatic = nullptr;
	}

	// Terrain QuadTree
	if (impl->terrain)
	{
		delete impl->terrain;
		impl->terrain = nullptr;
		Graphic::ins.scene.terrain = nullptr;
	}

	// BSP Source Map
	if (impl->sourceMap)
	{
		delete impl->sourceMap;
		impl->sourceMap = nullptr;
		Graphic::ins.scene.sourceMap = nullptr;
	}

	// BSP Quake Map
	if (impl->quakeMap)
	{
		delete impl->quakeMap;
		impl->quakeMap = nullptr;
		Graphic::ins.scene.quakeMap = nullptr;
	}

	// BSP Map
	if (impl->bspMap)
	{
		delete impl->bspMap;
		impl->bspMap = nullptr;
		Graphic::ins.scene.bspMap = nullptr;
	}

	// #EXTRA
}

void AreaMap::update()
{
	// float timeStep = Time::ins->getTimeStep();

	// newton::NewtonUpdate(this->world, timeStep);

	// // Enviroment update
	// this->physicDebug->update();

	if (impl->sourceMap)
		impl->sourceMap->update();

	if (impl->quakeMap)
		impl->quakeMap->update();

	if (impl->bspMap)
		impl->bspMap->update();

	for (Entity* ent : impl->lstEntities)
		ent->update();
}

void AreaMap::render()
{
	if (impl->sky)
		impl->sky->render();
	if (impl->terrainStatic)
		impl->terrainStatic->render();
	if (impl->terrain)
		impl->terrain->render();
	if (impl->sourceMap)
		impl->sourceMap->render();
	if (impl->quakeMap)
		impl->quakeMap->render();
	if (impl->bspMap)
		impl->bspMap->render();

	// Render nhieu lop doi voi graphic
	// while (Graphic::ins->needRenderMore())
	// {
		// // rende renviroment
		// this->physicDebug->render();
		// this->terrain->render();

		// Draw some cubes around
		for (Entity* ent : impl->lstEntities)
			ent->render();
	// }
}
