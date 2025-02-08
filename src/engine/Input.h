#ifndef __MT_INPUT_H__
#define __MT_INPUT_H__

#include "enumKey.h"

namespace mt {
namespace engine {

class Input {
public:

	// Variables
	static Input ins;

	// Forwards
	Input();
	~Input();

	void resetStatus();

	// Natives
	void keyPress(int idkey, bool state);
	void cursorPos(double xpos, double ypos, bool reset);
	bool checkPress(int idkey);
	bool checkHold(int idkey);
	bool checkRelease(int idkey);

	double getCursorX();
	double getCursorY();

	// Get / Set
	void setCallBackKeypress(void (*_func)(int key, bool state));

private:

	// Variables
	class InputImpl;
	InputImpl* impl;
};

}}

#endif
