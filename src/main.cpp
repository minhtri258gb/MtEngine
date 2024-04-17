#define __MT_MAIN_CPP__

#include "common.h"
#include "game/Game.h"
#include "test/Test.h"


using namespace std;
using namespace mt::game;
using namespace mt::test;

int main()
{
	#if 1
	Game::ins.run();
	#else
	Test program; // TEST
	program.run();
	#endif
	

	cout << "DONE." << endl;
	return 0;
}
