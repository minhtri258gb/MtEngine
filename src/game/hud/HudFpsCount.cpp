#define __MT_HUD_FPS_COUNT_CPP__

#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "graphic/Graphic.h"
#include "graphic/hud/Text.h"
#include "HudFpsCount.h"

using namespace std;
using namespace mt::graphic;
using namespace mt::game;


class HudFpsCount::HudFpsCountImpl
{
public:

	Text text;

};

HudFpsCount::HudFpsCount()
{
	// Implement
	impl = new HudFpsCountImpl();

	impl->text.init("ABCDEFGH", vec2(0.5, 0.5), 1.0f, vec3(0, 0, 0));
	Graphic::ins.gui.add(&impl->text);
}

HudFpsCount::~HudFpsCount()
{
	// Implement
	delete impl;
}

void HudFpsCount::load()
{

}

void HudFpsCount::clear()
{

}

void HudFpsCount::update()
{

}
