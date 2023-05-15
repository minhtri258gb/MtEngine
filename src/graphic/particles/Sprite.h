#ifndef __MT_SPRITE_H__
#define __MT_SPRITE_H__

#include "../ShaderProgram.h"

namespace mt {
namespace graphic {

class Sprite
{

public:

	// Variable
	static ShaderProgram shader;

	// Forward
	Sprite();
	~Sprite();
	void load(std::string name);
	void update();
	void render();

	// Native

private:

	class SpriteImpl;
	SpriteImpl* impl;

};

}}

#endif
