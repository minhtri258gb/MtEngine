#define __MT_SPRITE_CPP__

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

#include "common.h"
#include "graphic/Graphic.h"
#include "graphic/buffer/VertexArrayObject.h"
#include "graphic/texture/Texture.h"
#include "Sprite.h"

using namespace std;
using namespace mt::graphic;

ShaderProgram Sprite::shader;


class Sprite::SpriteImpl
{
public:
	VertexArrayObject VAO;
	Texture texture;
};

Sprite::Sprite()
{
	// Implement
	this->impl = new SpriteImpl();
}

Sprite::~Sprite()
{
	// Implement
	delete this->impl;
}

void Sprite::load(string name)
{
	// VAO
	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addDynamicAttribute(1024, vec3());
	impl->VAO.unbind();
	impl->VAO.setCount(1);

	// Texture
	// impl->texture.init("../res/textures/particles/christopher-carlson-charge-ring.jpg", true);
	impl->texture.init("../res/textures/particles/aHEiB5kn3N-yZ9VdtQPeXA.jpeg", true);
}

void Sprite::update()
{
}

void Sprite::render()
{
	shader.use();

	Graphic::ins.blendToogle(true);
	Graphic::ins.blendFunc(1);
	// Graphic::ins.cullFaceToogle(false);
	// Graphic::ins.wireframe(true);

	impl->texture.bind();

	impl->VAO.bind();

	vector<vec3> position;
	position.push_back(vec3(-0.5f,  0.5f, 0.0f));
	position.push_back(vec3(-0.5f, -0.5f, 0.0f));
	position.push_back(vec3( 0.5f,  0.5f, 0.0f));
	position.push_back(vec3( 0.5f, -0.5f, 0.0f));
	
	impl->VAO.updateDynamicAttribute(0, position);
	impl->VAO.drawPointInstance(position.size());
	impl->VAO.unbind();

	Graphic::ins.blendToogle(false);
	// Graphic::ins.cullFaceToogle(true);
	// Graphic::ins.wireframe(false);
}
