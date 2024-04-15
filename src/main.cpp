#define __MT_MAIN_CPP__

#include "common.h"
#include "game/Game.h"
#include "test/Test.h"

int main()
{
	#if 1
	mt::game::Game program; // ENGINE
	#else
	mt::test::Test program; // TEST
	#endif
	
	program.run();

	std::cout << "DONE." << std::endl;
	return 0;
}
