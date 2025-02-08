#ifndef __MT_HUD_H__
#define __MT_HUD_H__

namespace mt {
namespace game {

class Hud {

public:

	// Variable
	bool isActive;

	// Forward
	Hud();
	virtual ~Hud();
	virtual void load();
	virtual void clear();
	virtual void update();

protected:

};

}}

#endif
