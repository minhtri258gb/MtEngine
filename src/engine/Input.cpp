#define __MT_INPUT_CPP__

#define DEBUG_SHOW_BUTTON 0

#include <bitset>

#include "common.h"
#include "Input.h"

using namespace std;
using namespace mt::engine;

Input Input::ins;

class Input::InputImpl
{
public:
	bitset<354> keyPress;
	bitset<354> keyHold;
	bitset<354> keyRelease;
	double mx, my, dx, dy;
};

Input::Input()
{
	// Implement
	impl = new InputImpl();
}

Input::~Input()
{
	// Implement
	delete impl;
}

void Input::resetStatus()
{
	impl->keyPress.reset();
	impl->keyRelease.reset();
	impl->dx = 0.0;
	impl->dy = 0.0;
}

void Input::keyPress(int idkey, bool state)
{
	if (state)
	{
		#if DEBUG_SHOW_BUTTON
			cout << "key: " << idkey << endl;
		#endif

		impl->keyPress.set(idkey, true);
		impl->keyHold.set(idkey, true);
	}
	else
	{
		impl->keyRelease.set(idkey, true);
		impl->keyHold.set(idkey, false);
	}
}

void Input::cursorPos(double xpos, double ypos)
{
	impl->dx = xpos - impl->mx;
	impl->dy = impl->my - ypos;

	impl->mx = xpos;
	impl->my = ypos;

	// cout << vec2(impl->dx, impl->dy).length() << endl;
}

bool Input::checkPress(int idkey)
{
	return impl->keyPress.test(idkey);
}

bool Input::checkHold(int idkey)
{
	return impl->keyHold.test(idkey);
}

bool Input::checkRelease(int idkey)
{
	return impl->keyRelease.test(idkey);
}

double Input::getCursorX()
{
	return impl->dx;
}

double Input::getCursorY()
{
	return impl->dy;
}
