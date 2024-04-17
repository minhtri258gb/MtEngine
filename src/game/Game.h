#ifndef __MT_GAME_H__
#define __MT_GAME_H__

#include "maps/Map.h"
#include "hud/Screen.h"


namespace mt {
namespace game {

class Game {

public:

	// Variable
	static Game ins;
	Map* map;
	Screen screen;

	// Forward
	Game();
	~Game();
	void run();

	// Native

	// Stock

private:

	// Variable
	bool mainloop;

	// Forward
	void init();
	void framework();
	void close();

	// Native

};

}}

#endif
