#define __MT_GAME_CPP__

#define LOG cout << __FILE__ << " | " << __LINE__ << '\n';

#include <iostream>
#include <vector>
#include <map>

#include "engine/Timer.h"
#include "engine/math/Math.h"
#include "engine/datatype/3D/Math3D.h"
#include "engine/exception/Exception.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"
#include "Game.h"

// test import
#include "graphic/ShaderProgram.h"
#include "game/maps/MapBuilder.h"

// #include "graphic/models/animation/AnimationModel.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;

Game::Game()
{
	this->mainloop = true;
}

Game::~Game()
{
}

void Game::run()
{

	#ifdef LOG
	LOG
	#endif

	try
	{
		this->init();

		#ifdef LOG
		LOG
		#endif

		this->framework();

		#ifdef LOG
		LOG
		#endif
	
		this->close();
	
		#ifdef LOG
		LOG
		#endif
	
	}
	catch (Exception e)
	{
		
		#ifdef LOG
		LOG
		#endif
	
		cerr << "[ERROR]: " << e.getMessage() << '\n';
	}
	catch (std::exception e)
	{
		
		#ifdef LOG
		LOG
		#endif
	
		cerr << "[ERROR]: " << e.what() << '\n';
	}
	
	#ifdef LOG
	LOG
	#endif
	
}

void Game::init()
{
	// Init module
	Timer::ins.init();
	Graphic::ins.init();
	Physic::ins.init();

	// Init component
	this->map = MapBuilder::firstLoad();

	// #EXTRA
}

void Game::framework()
{
	#ifdef LOG
	LOG
	#endif

	// Before loop
	// Timer::ins.init();

	// Main loop
	while (this->mainloop)
	{
		// input
		Graphic::ins.processInput();

		// input network

		// loading
		this->map->load();

		// Physic
		Physic::ins.update();

		// Pre Process
		Graphic::ins.camera.update();

		// Map update
		this->map->update();

		// rendering commands here
		Graphic::ins.renderPre();

		#ifdef LOG
		LOG
		#endif

		// Map render
		this->map->render();

		#ifdef LOG
		LOG
		#endif

		// #ADD

		// reset state input

		// check and call events and swap the buffers
		if (!Graphic::ins.checkWindow())
			this->mainloop = false;
		Graphic::ins.renderPost();

		// Sync FPS
		Timer::ins.sleep();
	}
}

void Game::close()
{
	// Clear component
	
	// #EXTRA
	this->map->clear();
	delete this->map;

	// Close Module
	
	// #EXTRA
	
	Physic::ins.close();
	Graphic::ins.close();
}
