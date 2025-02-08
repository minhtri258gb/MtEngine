#define __MT_DEV_CPP__

#include "common.h"
#include "engine/Log.h"
// #include "graphic/Graphic.h"
// #include "graphic/ui/Panel.h"
// #include "game/Game.h"
#include "Dev.h"

using namespace std;
using namespace mt::engine;
// using namespace mt::graphic;
using namespace mt::game;


// Common
void Dev::test() {
	LOG("test");
	try {
		
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Dev::test_audio() {
	LOG("test_audio");
	try {
		
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Dev::test_physic() {
	LOG("test_physic");
	try {
		
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
