#define __MT_TEST_MAP_CPP__

#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "graphic/Graphic.h"
#include "TestMap.h"

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

#include "engine/file/FileCFG.h"

using namespace std;
using namespace mt::graphic;
using namespace mt::game;


class TestMap::TestMapImpl
{
public:

	// General
	string name;

	// Enviroment
	SkyBox* sky;
	StaticTerrain* terrainStatic;
	Terrain* terrain;
	BspSourceMap* sourceMap;
	BspQuakeMap* quakeMap;
	BspMap* bspMap;
	
	// Entities
	vector<Entity*> lstEntities;
};

TestMap::TestMap(string name)
{
	// Implement
	impl = new TestMapImpl();
	impl->name = name;
}

TestMap::~TestMap()
{
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

void TestMap::load()
{
	if (!this->needLoading)
		return;
	
	this->needLoading = false; // or not maybe

	// Load config
	string configPath = "./res/maps/" + impl->name + ".cfg";
	FileCFG fCFG(configPath);

	// Set general
	fCFG.select("general");
	int size = fCFG.getInt("size");

	// Set player position
	vec3 playerPos = fCFG.getVec3("player_posotion");
	Graphic::ins.camera.position = playerPos;


	// Load enviroment
	fCFG.select("enviroment");

	// =================== Sky ===================
	string skyName = fCFG.get("skybox");
	impl->sky = new SkyBox();
	impl->sky->init(skyName);

	// =================== Terrain Static ===================
	// impl->terrainStatic = new StaticTerrain();
	// impl->terrainStatic->init("chadvernon");

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
	GroundEnt* groundEnt = new GroundEnt("matdat");
	groundEnt->pos = vec3(0,-5,0);
	groundEnt->init();
	impl->lstEntities.push_back(groundEnt);

	// Load entities
	fCFG.select("entities");
	vector<string> lstEntCfg = fCFG.values();
	for (short i=0, sz=lstEntCfg.size(); i<sz; i++)
	{
		string entCfg = lstEntCfg.at(i);
		stringstream geek(entCfg);
		string entType, entName;
		geek >> entType >> entName;

		if (entType == "Test")
		{
			float x, y, z, rx, ry, rz, scale;
			geek >> x >> y >> z >> rx >> ry >> rz >> scale;

			TestEnt* ent = new TestEnt(entName);
			ent->pos = vec3(x, y, z);
			ent->rot = quat(rx, ry, rz);
			ent->scale = vec3(scale, scale, scale);
			ent->init();
			impl->lstEntities.push_back(ent);
		}
		else if (entType == "ModelV0")
		{

		}
		else if (entType == "ModelV1")
		{

		}
		else if (entType == "Particles")
		{

		}
		else
		{

		}
	}

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
	// impl->lstEntities.push_back(ent002);

	// HUD - Text
	// #TODO

	// #EXTRA
}

void TestMap::clear()
{
	for (Entity *ent : impl->lstEntities)
		delete ent;
	impl->lstEntities.clear();

	// Sky
	if (impl->sky)
	{
		delete impl->sky;
		impl->sky = nullptr;
	}

	// Terrain Static
	if (impl->terrainStatic)
	{
		delete impl->terrainStatic;
		impl->terrainStatic = nullptr;
	}

	// Terrain QuadTree
	if (impl->terrain)
	{
		delete impl->terrain;
		impl->terrain = nullptr;
	}

	// BSP Source Map
	if (impl->sourceMap)
	{
		delete impl->sourceMap;
		impl->sourceMap = nullptr;
	}

	// BSP Quake Map
	if (impl->quakeMap)
	{
		delete impl->quakeMap;
		impl->quakeMap = nullptr;
	}

	// BSP Map
	if (impl->bspMap)
	{
		delete impl->bspMap;
		impl->bspMap = nullptr;
	}

	// #EXTRA
}

void TestMap::update()
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

void TestMap::render()
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
