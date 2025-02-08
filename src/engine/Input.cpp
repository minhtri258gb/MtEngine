#define __MT_INPUT_CPP__

#define DEBUG_SHOW_BUTTON 0

#include <bitset>

#include "common.h"
#include "Log.h"
#include "Input.h"

using namespace std;
using namespace mt::engine;

Input Input::ins;


class Input::InputImpl {
public:
	bitset<354> keyPress;
	bitset<354> keyHold;
	bitset<354> keyRelease;
	double mx, my, dx, dy;

	void (*cbkKeypress)(int key, bool state); // Callback function pointer
};

Input::Input() {
	// Implement
	impl = new InputImpl();
}

Input::~Input() {
	// Implement
	delete impl;
}

void Input::resetStatus() {
	impl->keyPress.reset();
	impl->keyRelease.reset();
	impl->dx = 0.0;
	impl->dy = 0.0;
}

void Input::keyPress(int key, bool state) {
	LOG("keyPress");
	try {

		if (state) {
			#if DEBUG_SHOW_BUTTON
				cout << "key: " << idkey << endl;
			#endif

			impl->keyPress.set(key, true);
			impl->keyHold.set(key, true);
		}
		else {
			impl->keyRelease.set(key, true);
			impl->keyHold.set(key, false);
		}

		// Call cbk
		impl->cbkKeypress(key, state);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void Input::cursorPos(double xpos, double ypos, bool reset) {
	LOG("cursorPos");
	try {

		if (!reset) {
			impl->dx = xpos - impl->mx;
			impl->dy = impl->my - ypos;
		}
		else {
			impl->dx = 0;
			impl->dy = 0;
		}

		impl->mx = xpos;
		impl->my = ypos;

		// cout << vec2(impl->dx, impl->dy).length() << endl;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

bool Input::checkPress(int idkey) {
	return impl->keyPress.test(idkey);
}

bool Input::checkHold(int idkey) {
	return impl->keyHold.test(idkey);
}

bool Input::checkRelease(int idkey) {
	return impl->keyRelease.test(idkey);
}

double Input::getCursorX() {
	return impl->dx;
}

double Input::getCursorY() {
	return impl->dy;
}

void Input::setCallBackKeypress(void (*_func)(int key, bool state)) {
	impl->cbkKeypress = _func;
}
