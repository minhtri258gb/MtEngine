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
	this->impl = new InputImpl();
}

Input::~Input()
{
	// Implement
	delete this->impl;
}

void Input::resetStatus()
{
	this->impl->keyPress.reset();
	this->impl->keyRelease.reset();
	this->impl->dx = 0.0;
	this->impl->dy = 0.0;
}

void Input::keyPress(int idkey, bool state)
{
	if (state)
	{
		#if DEBUG_SHOW_BUTTON
			cout << "key: " << idkey << endl;
		#endif

		this->impl->keyPress.set(idkey, true);
		this->impl->keyHold.set(idkey, true);
	}
	else
	{
		this->impl->keyRelease.set(idkey, true);
		this->impl->keyHold.set(idkey, false);
	}
}

void Input::cursorPos(double xpos, double ypos)
{
	this->impl->dx = xpos - this->impl->mx;
	this->impl->dy = this->impl->my - ypos;

	this->impl->mx = xpos;
	this->impl->my = ypos;
}

bool Input::checkPress(int idkey)
{
	return this->impl->keyPress.test(idkey);
}

bool Input::checkHold(int idkey)
{
	return this->impl->keyHold.test(idkey);
}

bool Input::checkRelease(int idkey)
{
	return this->impl->keyRelease.test(idkey);
}

double Input::getCursorX()
{
	return this->impl->dx;
}

double Input::getCursorY()
{
	return this->impl->dy;
}
