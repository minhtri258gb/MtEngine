#define __MT_MAP_CPP__

#include "common.h"
#include "Map.h"

using namespace mt::game;

Map::Map()
{
	this->needLoading = true;
}

Map::~Map()
{
	
}

void Map::load()
{
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}

void Map::clear()
{
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}

void Map::update()
{
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}

void Map::render()
{
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}

void Map::setNeedLoad(bool _b)
{
	this->needLoading = _b;
}
