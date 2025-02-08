#ifndef __MT_GAME_H__
#define __MT_GAME_H__

#include "Screen.h"
#include "maps/Map.h"
#include "maps/MapBuilder.h"


namespace mt {
namespace game {

class Game {

public:

	// Variable
	static Game ins;
	Map* map;
	Screen screen;

	MapBuilder mapBuilder;

	// Forward
	Game();
	~Game();
	void run();

	// Native
	void exit();

	// Stock

private:

	// Variable
	bool m_mainloop;

	// Forward
	void init();
	void framework();
	void close();

	// Native

};

}}

#endif
