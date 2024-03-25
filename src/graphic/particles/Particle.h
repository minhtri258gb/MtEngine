#ifndef __MT_PARTICLE_H__
#define __MT_PARTICLE_H__

namespace mt {
namespace graphic {

class Particle
{
public:

	// Constructor
	Particle(float scale, float gravity, float maxlife);
	~Particle();

	// Framework
	void update();

	// General
	void respawn(vec3 pos, vec3 dir);

	// Get / Set
	vec3 getOrigin();
	float getScale();
	bool isAlive();
	float getProgress();

private:

	// Variable
	vec3 origin, velocity;
	float scale, gravity, life, maxlife;

};

}}

#endif
