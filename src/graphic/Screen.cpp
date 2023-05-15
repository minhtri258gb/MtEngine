#define __MT_SCREEN_CPP__

#include "common.h"
#include "engine/Config.h"
#include "Graphic.h"
#include "Screen.h"

using namespace mt::engine;
using namespace mt::graphic;

Screen::Screen()
{
}

Screen::~Screen()
{
}

void Screen::init()
{
	// Data
	int width = Config::ins.windowWidth;
	int height = Config::ins.windowHeight;

	// Variable
	this->proj.ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);
	this->view = mat4();

	// Set shader
	Graphic::ins.shaderProgramMgr.setScreenProj(proj);
}
