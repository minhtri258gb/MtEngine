#define __MT_GAME_CPP__

// #define LOG

#include "common.h"
#include "Game.h"
#include "engine/Timer.h"
#include "graphic/Graphic.h"
#include "physic/Physic.h"

// test import
#include "graphic/ShaderProgram.h"
#include "game/maps/LobbyMap.h"

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
	cout << __FILE__ << " | " << __LINE__ << '\n';
	#endif

	try
	{
		this->init();

		#ifdef LOG
		cout << __FILE__ << " | " << __LINE__ << '\n';
		#endif

		this->framework();

		#ifdef LOG
		cout << __FILE__ << " | " << __LINE__ << '\n';
		#endif
	
		this->close();
	
		#ifdef LOG
		cout << __FILE__ << " | " << __LINE__ << '\n';
		#endif
	
	}
	catch (Exception e)
	{
		
		#ifdef LOG
		cout << __FILE__ << " | " << __LINE__ << '\n';
		#endif
	
		cerr << "[ERROR]: " << e.getMessage() << '\n';
	}
	catch (std::exception e)
	{
		
		#ifdef LOG
		cout << __FILE__ << " | " << __LINE__ << '\n';
		#endif
	
		cerr << "[ERROR]: " << e.what() << '\n';
	}
	
	#ifdef LOG
	cout << __FILE__ << " | " << __LINE__ << '\n';
	#endif
	
}

void Game::init()
{
	// Init module
	Timer::ins.init();
	Graphic::ins.init();
	Physic::ins.init();

	// Init component
	this->map = new LobbyMap();

	// #EXTRA
}

void Game::framework()
{
	#ifdef LOG
	cout << __FILE__ << " | " << __LINE__ << '\n';
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

		// rendering commands here
		Graphic::ins.renderPre();

		#ifdef LOG
		cout << __FILE__ << " | " << __LINE__ << '\n';
		#endif

		// Map render
		this->map->render();

		#ifdef LOG
		cout << __FILE__ << " | " << __LINE__ << '\n';
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
