#define __MT_LOBBY_MAP_CPP__

#include "common.h"
#include "graphic/Graphic.h"
#include "LobbyMap.h"

#include "../../graphic/sky/SkyBox.h"
#include "../../graphic/terrain/StaticTerrain.h"
#include "../../graphic/terrain/Terrain.h"

#include "../entities/TestEnt.h"
#include "../entities/GroundEnt.h"
#include "../entities/TestAnimEnt.h"
#include "../entities/TestParticleEnt.h"

using namespace std;
using namespace mt::graphic;
using namespace mt::game;

class LobbyMap::LobbyMapImpl
{
public:
	SkyBox* sky;
	StaticTerrain* terrainStatic;
	// Terrain* terrain;
};

LobbyMap::LobbyMap()
{
	// Implement
	impl = new LobbyMapImpl();
}

LobbyMap::~LobbyMap()
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

void LobbyMap::load()
{
	if (!this->needLoading)
		return;
	
	this->needLoading = false; // or not maybe


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
	// SphereEnt* sphereEnt = new SphereEnt();
	// sphereEnt->position = vec3(0, 100, 0);
	// sphereEnt->radius = 1.0f;
	// sphereEnt->color = vec4i(0, 0, 0, 255);
	// sphereEnt->initBody(true);
	// this->lstEntitiesDynamic.push_back(sphereEnt);

	// Test Entity
	// this->lstEntitiesStatic.push_back(new TestEnt("test"));
	// this->lstEntitiesStatic.push_back(new TestEnt("box"));

	this->lstEntitiesStatic.push_back(new GroundEnt("matdat"));
	// this->lstEntitiesStatic.push_back(new TestAnimEnt("asd")); // Test animation model // OKE
	// this->lstEntitiesStatic.push_back(new TestParticleEnt("test"));

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

	// Sky
	// impl->sky = new SkyBox();
	// impl->sky->init("blabla");

	// Terrain
	impl->terrainStatic = new StaticTerrain();
	impl->terrainStatic->init("hm1");

	// impl->terrain = new Terrain();
	// impl->terrain->init("something");

	// HUD - Text
	// #TODO

	// #EXTRA
}

void LobbyMap::clear()
{
	for (Entity *ent : this->lstEntitiesStatic)
		delete ent;
	this->lstEntitiesStatic.clear();

	// Sky
	if (impl->sky)
	{
		delete impl->sky;
		impl->sky = nullptr;
	}

	// Terrain
	// if (impl->terrainStatic)
	// {
	// 	delete impl->terrainStatic;
	// 	impl->terrainStatic = nullptr;
	// }
	// if (impl->terrain)
	// {
	// 	delete impl->terrain;
	// 	impl->terrain = nullptr;
	// }

	// #EXTRA
}

void LobbyMap::update()
{
	// float timeStep = Time::ins->getTimeStep();

	// newton::NewtonUpdate(this->world, timeStep);

	// // Enviroment update
	// this->physicDebug->update();

	// for (Entity* ent : this->lstEntitiesDynamic)
	// {
	// 	ent->update();
	// }

}

void LobbyMap::render()
{
	// sky
	if (impl->sky)
		impl->sky->render();

	if (impl->terrainStatic)
		impl->terrainStatic->render();
	
	// if (impl->terrain)
	// 	impl->terrain->render();
	
	// Render nhieu lop doi voi graphic
	// while (Graphic::ins->needRenderMore())
	// {
		// // rende renviroment
		// this->physicDebug->render();
		// this->terrain->render();

		// Draw some cubes around
		for (Entity* ent : this->lstEntitiesStatic)
			ent->render();

		// for (Entity* ent : this->lstEntitiesDynamic)
		// {
		// 	ent->render();
		// }
	// }
}
