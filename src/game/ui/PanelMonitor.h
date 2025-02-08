#ifndef __MT_PANEL_MONITOR_H__
#define __MT_PANEL_MONITOR_H__

#include "graphic/ui/Panel.h"

namespace mt {
namespace game {

class PanelMonitor : public graphic::Panel {
public:

	// Variables

	// Static method

	// Forwards
	PanelMonitor();
	~PanelMonitor();

	void render();

	// Natives

private:

	// Variables
	bool m_fps;
	bool m_origin;
};

}}

#endif
