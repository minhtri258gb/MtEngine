#define __MT_FLAG_32_CPP__

#include "Flag32.h"

using namespace mt::engine;

Flag32::Flag32()
{
	// unsigned char flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
	core = 0;
}

Flag32::Flag32(unsigned int value)
{
	core = value;
}

Flag32::~Flag32()
{
}

bool Flag32::check(unsigned int mark)
{
	return core & (1 << mark);
}

void Flag32::setOn(unsigned int mark)
{
	core |= (1 << mark);
}

void Flag32::setOff(unsigned int mark)
{
	core &= ~(1 << mark);
}

void Flag32::setFlip(unsigned int mark)
{
	core ^= (1 << mark);
}

unsigned int Flag32::get()
{
	return core;
}
