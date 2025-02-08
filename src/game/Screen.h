#ifndef __MT_SCREEN_H__
#define __MT_SCREEN_H__

#include "../graphic/ui/Panel.h"
#include "hud/Hud.h"

namespace mt {
namespace game {

class Screen {

public:

	// Consstructor
	Screen();
	~Screen();

	// General
	void init();
	void update();
	void close();

	// Method
	Hud* getHud(std:: string name);
	void add(std::string name, Hud* hud);

	graphic::Panel* getPanel(std:: string name);
	bool togglePanel(std:: string name);
	void add(std::string name, graphic::Panel* panel);

protected:

private:

	// Variables
	class ScreenImpl;
	ScreenImpl* impl;

};

}}

#endif
