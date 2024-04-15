#define __MT_INTERFACE_CPP__

#include "common.h"
#include "engine/Config.h"
#include "GUI.h"
#include "graphic/Graphic.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


class GUI::GUIImpl
{
public:

};

GUI::GUI()
{
	// Implement
	impl = new GUIImpl();
}

GUI::~GUI()
{
	// Implement
	delete impl;
}

void GUI::init()
{
	float width = Config::ins.windowWidth;
	float height = Config::ins.windowHeight;

	this->proj.ortho(0.0f, (float)width, 0.0f, (float)height); // , 0.0f, 10.0f

	Graphic::ins.shaderProgramMgr.setScreenProj(proj);

	// Init component
	Text::initText();
}

void GUI::update()
{
}

void GUI::render()
{
	for (uint i=0, sz=this->lstText.size(); i<sz; i++)
	{
		this->lstText.at(i)->render();
	}
}

void GUI::add(Text* text)
{
	this->lstText.push_back(text);
}
