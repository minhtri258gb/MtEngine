#ifndef __MT_PANEL_H__
#define __MT_PANEL_H__

namespace mt {
namespace graphic {

class Panel {
public:

	// Static method

	// Forwards
	Panel();
	virtual ~Panel();

	virtual void render();

	// Natives
	bool isShow();
	void show(bool toggle);

protected:

	// Variables
	bool m_show;

};

}}

#endif
