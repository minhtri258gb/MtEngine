#define __MT_SCREEN_CPP__

#include "common.h"
#include "Screen.h"

using namespace mt::game;

Screen::Screen()
{
	
}

Screen::~Screen()
{
	
}

void Screen::init()
{
	
}

void Screen::clear()
{
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}

void Screen::update()
{
	for (uint i=0, sz=this->lstHud.size(); i<sz; i++)
	{
		Hud* hud = this->lstHud.at(i);
		if (!hud->isActive)
			continue;
		
		hud->update();
	}
}

uint Screen::add(Hud* _hud)
{
	this->lstHud.push_back(_hud);
	return this->lstHud.size() - 1;
}
