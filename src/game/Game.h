#ifndef __MT_GAME_H__
#define __MT_GAME_H__

#include "maps/Map.h"

namespace mt {
namespace game {

class Game {

public:

	// Variable
	Map* map;

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
