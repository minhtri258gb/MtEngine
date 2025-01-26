#define __MT_GAME_CPP__

// #define LOG cout << __FILE__ << " | " << __LINE__ << '\n';

#include <iostream>
#include <vector>
#include <map>
#include <stacktrace>

#include "common.h"

#include "engine/Timer.h"
#include "engine/math/Math.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"
#include "Game.h"
#include "game/CommandMgr.h"
#include "game/maps/MapBuilder.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


Game Game::ins;

Game::Game() {
	this->mainloop = true;
}

Game::~Game() {
}

void Game::run() {

	#ifdef LOG
	LOG
	#endif

	try {
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
	catch (Exception e) {

		#ifdef LOG
		LOG
		#endif

		cerr << "[ERROR]: " << std::endl << e.getMessage() << '\n';
	}
	catch (exception &e) {
		
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
	try {
		// Init module
		Timer::ins.init();
		Graphic::ins.init();
		Physic::ins.init();
		CommandMgr::ins.init();

		#ifdef LOG
		LOG
		#endif
		
		// Init component
		this->screen.init();
		this->map = MapBuilder::firstLoad();

		// #EXTRA
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void Game::framework()
{
	try {
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

			#ifdef LOG
			LOG
			#endif

			// Input network

			#ifdef LOG
			LOG
			#endif
			
			// Process Command
			CommandMgr::ins.update();

			// loading
			this->map->load();

			#ifdef LOG
			LOG
			#endif
			
			// Physic
			Physic::ins.update();

			#ifdef LOG
			LOG
			#endif
			
			// Pre Process
			Graphic::ins.camera.update();

			#ifdef LOG
			LOG
			#endif
			
			// Map update
			this->map->update();

			#ifdef LOG
			LOG
			#endif
			
			// rendering commands here
			Graphic::ins.renderPre();

			#ifdef LOG
			LOG
			#endif

			// Bind Buffer

			// Map render
			// this->map->render();

			// End Bind

			// Render Screen PostProcess

			// Render HUD

			// Graphic
			Graphic::ins.render();

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
	catch (Exception e) {
		track(e);
		throw e;
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
