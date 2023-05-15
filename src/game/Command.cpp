#define __MT_COMMAND_CPP__

#include "common.h"
#include "Command.h"

#include "../engine/enumKey.h"

using namespace std;
using namespace mt::game;

Command Command::ins;

class Command::CommandImpl
{
public:
};

Command::Command()
{
	// Implement
	this->impl = new CommandImpl();
}

Command::~Command()
{
	// Implement
	delete this->impl;
}
