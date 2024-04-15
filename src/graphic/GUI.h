#ifndef __MT_GUI_H__
#define __MT_GUI_H__

#include "hud/Text.h"


namespace mt {
namespace graphic {

class GUI
{

public:

	// Variable
	mat4 proj;
	std::vector<Text*> lstText;
	
	// Forward
	GUI();
	~GUI();

	void init();
	void update();
	void render();

	// Native
	void add(Text* text);

private:

	// Variable
	class GUIImpl;
	GUIImpl* impl;

};

}}

#endif
