#ifndef __MT_EMITTER_H__
#define __MT_EMITTER_H__

#include "../ShaderProgram.h"
// #include "../../graphic/shader/Shader.h"
// #include "../../graphic/vertexbuffer/VertexBuffer.h"
// #include "../../graphic/texture/TextureAtlas.h"
#include "Particle.h"

namespace mt {
namespace graphic {

class Emitter
{
public:

	// Static
	static ShaderProgram shader;

	// Variable
	std::string name;
	vec3 originB, originE, velocityB, velocityE;

	// Constructor
	Emitter();
	~Emitter();

	// General
	void init(std::string name, std::list<Particle*> &particles);
	void del(std::list<Particle*> &particles);

    // Framework
	void update(std::list<Particle*> &particles, bool isSpawn);
	void render(std::list<Particle*> &particles);

private:

	class EmitterImpl;
	EmitterImpl* impl;

};

}}

#endif
