#define __MT_HUD_CPP__

#include "common.h"
#include "Hud.h"

using namespace mt::game;


Hud::Hud() {

	// Default
	this->isActive = true;
}

Hud::~Hud() {
}

void Hud::load() {
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}

void Hud::update() {
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}

void Hud::clear() {
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}
