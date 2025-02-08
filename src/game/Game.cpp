#define __MT_GAME_CPP__

#include <iostream>
#include <vector>
#include <map>
#include <stacktrace>

#include "common.h"

#include "engine/Log.h"
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
	LOG("Game");
	try {
		this->m_mainloop = true;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
Game::~Game() {
	LOG("~Game");
}

void Game::run() {
	LOG("run");
	try {

		this->init();

		this->framework();

		this->close();
	}
	catch (Exception e) {
		track(e);
		cerr << "[ERROR]: " << std::endl << e.getMessage() << '\n';
	}
	catch (exception &e) {
		cerr << "[ERROR]: " << e.what() << '\n';
	}
}
void Game::init() {
	LOG("init");
	try {

		// Init module
		Timer::ins.init();
		Graphic::ins.init();
		Physic::ins.init();
		CommandMgr::ins.init();

		// Init component
		this->screen.init();
		this->map = this->mapBuilder.firstLoad();

		// #EXTRA
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Game::framework() {
	LOG("framework");
	try {

		// Before loop
		// Timer::ins.init();

		// Main loop
		while (this->m_mainloop) {

			// input
			// Graphic::ins.processInput();

			// Input network

			// Process Command
			CommandMgr::ins.update();

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

			// Bind Buffer

			// Map render
			// this->map->render();

			// End Bind

			// Render Screen PostProcess

			// Render HUD

			// Graphic
			Graphic::ins.render();

			// #ADD

			// reset state input

			// check and call events and swap the buffers
			if (!Graphic::ins.checkWindow())
				this->m_mainloop = false;
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
void Game::close() {
	LOG("close");
	try {
		// Clear component

		// #EXTRA
		this->map->clear();
		delete this->map;

		// Close Module

		// #EXTRA

		Physic::ins.close();
		Graphic::ins.close();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void Game::exit() {
	LOG("exit");
	try {
		this->m_mainloop = false;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
