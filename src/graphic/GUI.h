#ifndef __MT_GUI_H__
#define __MT_GUI_H__

#include "ui/Text.h"
#include "ui/Panel.h"


namespace mt {
namespace graphic {

class GUI {

public:

	// Variable
	mat4 proj;
	std::vector<Text*> lstText;
	std::vector<Panel*> lstPanel;

	// Forward
	GUI();
	~GUI();

	void init();
	void update();
	void render();
	void close();

	// Native
	void add(Text* text);
	void add(Panel* panel);

private:

	// Variable
	class GUIImpl;
	GUIImpl* impl;

};

}}

#endif
