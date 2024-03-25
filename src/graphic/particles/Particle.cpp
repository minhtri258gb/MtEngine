#define __MT_PARTICLE_CPP__

#include "common.h"
#include "engine/Timer.h"
#include "Particle.h"

using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


Particle::Particle(float scale, float gravity, float maxlife)
{
	this->scale = scale;
	this->gravity = gravity;
	this->maxlife = maxlife;
	this->origin = this->velocity = vec3();
	this->life = 0;
}

Particle::~Particle()
{
}

void Particle::update()
{
	float elapsedTime = Timer::ins.getTimePassed();

	// Movement
	velocity.y = velocity.y - (gravity * elapsedTime);
	origin = origin + (velocity * elapsedTime);

	// Time pass
	life += elapsedTime;
}

vec3 Particle::getOrigin()
{
	return origin;
}

float Particle::getScale()
{
	return scale;
}

float Particle::getProgress()
{
	return life / maxlife;
}

void Particle::respawn(vec3 pos, vec3 dir)
{
	origin = pos;
	velocity = dir;
	life = 0;
}

bool Particle::isAlive()
{
	return life < maxlife;
}
