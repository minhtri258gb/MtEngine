#define __MT_ENTITY_CPP__

#include "common.h"
#include "Entity.h"

using namespace mt::game;

Entity::Entity()
{
	
}

Entity::~Entity()
{
	
}

void Entity::update()
{
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}

void Entity::render()
{
	std::cout << "\033[0;31mERROR\033[0m: " << __FILE__ << ", " << __LINE__ << std::endl;
}
