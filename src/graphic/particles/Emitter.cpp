#define __MT_EMITTER_CPP__

#include <list>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "engine/Random.h"
#include "engine/file/FileCFG.h"
#include "graphic/Graphic.h"
#include "graphic/buffer/VertexArrayObject.h"
#include "graphic/texture/TextureAtlas.h"
#include "Emitter.h"

#define PROBABILITY 1

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;

const short MAX_INSTANCE = 1024;
const short INSTANCE_DATA_LENGTH = 21;

// VertexBuffer Emitter::s_vb;
//unsigned int Emitter::s_vboID2;

ShaderProgram Emitter::shader;


class Emitter::EmitterImpl
{
public:

	// Component
	VertexArrayObject VAO;
	TextureAtlas texture;
};

// void Emitter::init()
// {
// 	// Shader
// 	s_shader.init("particle");
// 	s_shader.use();
// 	s_shader.addVariable("projection");		// 0
// 	s_shader.addVariable("ourTexture");		// 1
// 	s_shader.addVariable("numOfRows");		// 2

// 	// Vertex Buffer
// 	vector<vec2> vertices;
// 	vertices.push_back(vec2(-0.5f, -0.5f));
// 	vertices.push_back(vec2(0.5f, -0.5f));
// 	vertices.push_back(vec2(-0.5f, 0.5f));
// 	vertices.push_back(vec2(0.5f, 0.5f));

// 	s_vb.init();
// 	s_vb.bind();
// 	s_vb.addStaticAttribute(vertices);
// 	s_vb.addStreamAttribute(4, MAX_INSTANCE);
// 	s_vb.addStreamAttribute(4, MAX_INSTANCE);
// 	s_vb.addStreamAttribute(4, MAX_INSTANCE);
// 	s_vb.addStreamAttribute(4, MAX_INSTANCE);
// 	s_vb.addStreamAttribute(1, MAX_INSTANCE);
// 	s_vb.setAttribDivisor(0, 0);
// 	s_vb.setAttribDivisor(1, 1);
// 	s_vb.setAttribDivisor(2, 1);
// 	s_vb.setAttribDivisor(3, 1);
// 	s_vb.setAttribDivisor(4, 1);
// 	s_vb.setAttribDivisor(5, 1);
// 	s_vb.setAttribDivisor(6, 1);
// 	s_vb.setCount(4);
// 	s_vb.unbind();
// }

bool distanceParticle(Particle *&first, Particle *&second)
{
	vec3 camPos = Graphic::ins.camera.position;
	float dis1 = (first->getOrigin() - camPos).length();
	float dis2 = (second->getOrigin() - camPos).length();
	return dis1 > dis2;
}

Emitter::Emitter()
{
	// Implement
	this->impl = new EmitterImpl();
}

Emitter::~Emitter()
{
	// Implement
	delete this->impl;
}

void Emitter::init(string name, list<Particle*> &particles)
{
	// Load config
	this->name = name;
	string pathDir = "../res/sprites/emitter/" + name + "/";
	FileCFG* fCFG = new FileCFG(pathDir + "info.cfg");

	fCFG->select("general");
	string textureName = fCFG->get("texture");
	int column = fCFG->getInt("column");
	int row = fCFG->getInt("row");
	int maxParticle = fCFG->getInt("max_particle");
	vec2 scale = fCFG->getVec2("scale");
	float gravity = fCFG->getFloat("gravity");
	vec2 lifeTime = fCFG->getVec2("life");

	// Validate Max Particle
	if (maxParticle > MAX_INSTANCE)
		maxParticle = MAX_INSTANCE;

	// Load texture
	impl->texture.init(pathDir + textureName, column, row);

	// Gen particle
	for (short i = 0; i < maxParticle; i++)
		particles.push_back(new Particle(
				Random::ins.rangeF(scale.x, scale.y),
				gravity,
				Random::ins.rangeF(lifeTime.x, lifeTime.y)
				));
	
	// Prepare VAO
	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addDynamicAttribute(MAX_INSTANCE, vec3()); // position
	impl->VAO.addDynamicAttribute(MAX_INSTANCE, 0.0f); // scale
	impl->VAO.addDynamicAttribute(MAX_INSTANCE, 0.0f); // progress
	impl->VAO.unbind();
	impl->VAO.setCount(1);
}

void Emitter::del(list<Particle*> &particles)
{
	for (Particle *particle : particles)
		delete particle;
}

void Emitter::update(list<Particle*> &particles, bool isSpawn)
{
	bool spawn = isSpawn;
	for (Particle *particle : particles)
	{
		if (particle->isAlive())
			particle->update();
		else if (spawn)
		{
			spawn = false;

			vec3 origin;
			origin.x = Random::ins.rangeF(originB.x, originE.x);
			origin.y = Random::ins.rangeF(originB.y, originE.y);
			origin.z = Random::ins.rangeF(originB.z, originE.z);

			vec3 velocity;
			velocity.x = Random::ins.rangeF(velocityB.x, velocityE.x);
			velocity.y = Random::ins.rangeF(velocityB.y, velocityE.y);
			velocity.z = Random::ins.rangeF(velocityB.z, velocityE.z);

			particle->respawn(origin, velocity);
			particle->update();
		}
	}

	particles.sort(distanceParticle);
}

void Emitter::render(list<Particle*> &particles)
{
	// if (Graphic::ins.scene.getScene() != VIEW)
	// 	return;

//	if (!FrustumCulling::isSphereInFrustum(m_origin, 20.0f))
//		return;

	this->shader.use();

	Graphic::ins.blendFunc(1);
	Graphic::ins.blendToogle(true);
	Graphic::ins.setDepthMark(false);

	impl->texture.bind(); // Bind Texture
	this->shader.setVec2I(3, vec2i(impl->texture.getColumn(), impl->texture.getRow())); // Uniform colrowNum

	int maxParticle = particles.size();
	int bufferSize = maxParticle * INSTANCE_DATA_LENGTH;
	vector<vec3> positions;
	vector<float> scales;
	vector<float> progress;

	short countParticleAlive = 0;
	for (Particle *particle : particles)
	{
		if (!particle->isAlive())
			continue;

		countParticleAlive++;

		// Position
		positions.push_back(particle->getOrigin());
		scales.push_back(particle->getScale());
		progress.push_back(particle->getProgress());
	}

	impl->VAO.bind();
	impl->VAO.updateDynamicAttribute(0, positions);
	impl->VAO.updateDynamicAttribute(1, scales);
	impl->VAO.updateDynamicAttribute(2, progress);
	impl->VAO.drawPointInstance(countParticleAlive);
	impl->VAO.unbind();

	Graphic::ins.blendFunc(0);
	Graphic::ins.blendToogle(false);
	Graphic::ins.setDepthMark(true);
}
