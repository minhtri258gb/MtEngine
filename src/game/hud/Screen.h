#ifndef __MT_SCREEN_H__
#define __MT_SCREEN_H__

#include "Hud.h"

namespace mt {
namespace game {

class Screen
{

public:

	// Consstructor
	Screen();
	~Screen();

	// General
	void init();
	void clear();
	void update();

	// Method
	uint add(Hud*);

protected:

	// Variable
	std::vector<Hud*> lstHud;

};

}}

#endif
