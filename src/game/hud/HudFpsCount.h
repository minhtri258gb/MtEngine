#ifndef __MT_HUD_FPS_COUNT_H__
#define __MT_HUD_FPS_COUNT_H__

#include "Hud.h"

namespace mt {
namespace game {

class HudFpsCount : public Hud
{

public:

	HudFpsCount();
	~HudFpsCount();
	
	void load();
	void clear();
	void update();

private:

	// Variable
	class HudFpsCountImpl;
	HudFpsCountImpl* impl;

};

}}

#endif
