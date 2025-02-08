#define __MT_COMMAND_MGR_CPP__

#define MAX_KEY 354

#include <array>
#include <bitset>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "engine/Input.h"
#include "engine/enumKey.h"
#include "engine/file/FileCFG.h"

#include "CommandMgr.h"
#include "game/Command.h"

// revert include
#include "game/Game.h"

using namespace std;
using namespace mt::engine;
using namespace mt::game;


CommandMgr CommandMgr::ins;

class CommandMgr::CommandMgrImpl {
public:

	// Variable
	array<function, MAX_KEY> lstFunc; // Danh sach key - chuc nang
	bitset<MAX_KEY> keyAction;
	bitset<MAX_KEY> keyLoop;
	map<string, uint> convertKey;
	map<string, function> convertFunc;

	// Init Convert map
	void initConvertMap();
};

CommandMgr::CommandMgr() {

	// Implement
	this->impl = new CommandMgrImpl();
}

CommandMgr::~CommandMgr() {

	// Implement
	delete this->impl;
}

void CommandMgr::init() {
	LOG("init");
	try {

		// Init Convert map
		impl->initConvertMap();

		// Reset all Func
		for (int i=0; i<MAX_KEY; i++)
			impl->lstFunc[i] = &Command::cmd_void;

		// Load keybind
		FileCFG fKeyBind(Config::ins.system_path + "keybind.cfg");
		vector<string> lstKey = fKeyBind.keys();
		vector<string> lstFunc = fKeyBind.values();
		for (uint i=0, sz=lstKey.size(); i<sz; i++)
			this->keyBind(lstKey.at(i), lstFunc.at(i));

		// Set callback
		Input::ins.setCallBackKeypress(&CommandMgr::cbk_keypress);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void CommandMgr::update() {
	LOG("update");
	try {
		for (int i=0; i<MAX_KEY; i++) {
			if (impl->keyAction.test(i)) {

				// Off key no loop
				if (!impl->keyLoop.test(i))
					impl->keyAction.set(i, false);

				// Run function
				(*impl->lstFunc.at(i))();
			}
		}
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void CommandMgr::keyBind(string key, string func) {
	LOG("keyBind");
	// LOG("keyBind: key="+key+", func="+func);
	try {

		// Validate
		if (impl->convertKey.find(key) == impl->convertKey.end())
			throw error("KEY_INVAIL", "Invail Key \"" + key + "\"");

		int keyid = impl->convertKey.at(key);
		if (keyid == -1)
			throw error("KEY_NOT_FOUND", "Key \"" + key + "\" not found");

		if (impl->convertFunc.find(func) == impl->convertFunc.end())
			throw error("FUNCTION_NOT_FOUND", "Function \"" + func + "\" not found");

		impl->keyLoop.set(keyid, func[0] == '+' ? true : false);
		impl->lstFunc[keyid] = impl->convertFunc.at(func);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

void CommandMgr::cbk_keypress(int key, bool state) {
	CommandMgr::ins.impl->keyAction[key] = state;
}

void CommandMgr::CommandMgrImpl::initConvertMap() {
	LOG("initConvertMap");
	try {

		// KeyMap
		for (uint i=48; i<=57; i++)
			convertKey.insert({string(1, char(i)), i}); // 0 - 9
		for (uint i=65; i<=90; i++)
			convertKey.insert({string(1, char(i)), i}); // A - Z
		for (uint i=1; i<=25; i++)
			convertKey.insert({string("F") + to_string(i), 289 + i}); // F1 - F25
		for (uint i=0; i<=9; i++)
			convertKey.insert({string("KP_") + to_string(i), 320 + i}); // KP_0 - KP_9

		convertKey.insert({"BACKSPACE", 259});
		convertKey.insert({"CAPS_LOCK", 280});
		convertKey.insert({"DELETE", 261});
		convertKey.insert({"DOWN", 264});
		convertKey.insert({"ESCAPE", 256});
		convertKey.insert({"ENTER", 257});
		convertKey.insert({"END", 269});
		convertKey.insert({"HOME", 269});
		convertKey.insert({"INSERT", 269});

		convertKey.insert({"KP_DECIMAL", 330});
		convertKey.insert({"KP_DIVIDE", 331});
		convertKey.insert({"KP_MULTIPLY", 332});
		convertKey.insert({"KP_SUBTRACT", 333});
		convertKey.insert({"KP_ADD", 334});
		convertKey.insert({"KP_ENTER", 335});
		convertKey.insert({"KP_EQUAL", 336});

		convertKey.insert({"LEFT_SHIFT", 340});
		convertKey.insert({"LEFT_CONTROL", 341});
		convertKey.insert({"LEFT_ALT", 342});
		convertKey.insert({"LEFT_SUPER", 343});
		convertKey.insert({"LEFT", 263});

		convertKey.insert({"MOUSE1", 351});
		convertKey.insert({"MOUSE2", 352});
		convertKey.insert({"MOUSE3", 353});
		convertKey.insert({"MWHEELDOWN", 349});
		convertKey.insert({"MWHEELUP", 350});
		convertKey.insert({"MENU", 348});
		convertKey.insert({"NUM_LOCK", 282});
		convertKey.insert({"PRINT_SCREEN", 283});
		convertKey.insert({"PAUSE", 284});
		convertKey.insert({"PAGE_UP", 266});
		convertKey.insert({"PAGE_DOWN", 267});

		convertKey.insert({"RIGHT_SHIFT", 344});
		convertKey.insert({"RIGHT_SUPER", 347});
		convertKey.insert({"RIGHT_CONTROL", 345});
		convertKey.insert({"RIGHT_ALT", 346});
		convertKey.insert({"RIGHT", 262});

		convertKey.insert({"SPACE", 32});
		convertKey.insert({"SCROLL_LOCK", 281});
		convertKey.insert({"TAB", 258});
		convertKey.insert({"UP", 265});

		convertKey.insert({string(1, '\''), 39});
		convertKey.insert({string(1, ',' ), 44});
		convertKey.insert({string(1, '-' ), 45});
		convertKey.insert({string(1, '.' ), 46});
		convertKey.insert({string(1, '/' ), 47});
		convertKey.insert({string(1, ';' ), 59});
		convertKey.insert({string(1, '=' ), 61});
		convertKey.insert({string(1, '[' ), 91});
		convertKey.insert({string(1, '\\'), 92});
		convertKey.insert({string(1, ']' ), 93});
		convertKey.insert({string(1, '`' ), 96});

		// FuncMap
		Command::setFuncMap(&convertFunc);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

// int Command::CommandImpl::convertKey(string key)
// {
// 	int length = key.length();
// 	if (!length) return -1;
// 	int firstchar = key[0];
// 	if (64 < firstchar && firstchar < 91) {
// 		if (length == 1) return firstchar;							// A - Z
// 		else {
// 			switch (firstchar) {
// 			case 'B':
// 				if (key[1] == 'A') return 259; break;				// BACKSPACE
// 			case 'C':
// 				if (key[1] == 'A') return 280; break;				// CAPS_LOCK
// 			case 'D':
// 				if (key[1] == 'E') return 261;						// DELETE
// 				else if (key[1] == 'O') return 264;					// DOWN
// 				break;
// 			case 'E':
// 				if (key[1] == 'S') return 256;						// ESCAPE
// 				else if (key[1] == 'N') {
// 					if (key[2] == 'T') return 257;					// ENTER
// 					else if (key[2] == 'D') return 269;				// END
// 				}
// 				break;
// 			case 'F':
// 				if (key[1] == '1') {
// 					if (length == 2) return 290;						// F1
// 					else return 251 + key[2];						// F10 - F11
// 				} else if (key[1] == '2') {
// 					if (length == 2) return 291;						// F1
// 					else {											// F20 - F25
// 						if (261 + key[2] < 315) return 261 + key[2];
// 					}
// 				} else if (key[1] != '0') return 241 + key[1];		// F3 - F9
// 				break;
// 			case 'H':
// 				if (key[1] == 'O') return 268;						// HOME
// 				break;
// 			case 'I':
// 				if (key[1] == 'N') return 260;						// INSERT
// 				break;
// 			case 'K':
// 				if (key[3] < 65) return 272 + key[3];				// KP_0 - KP_9
// 				else if (key[3] == 'D') {
// 					if (key[4] == 'E') return 330;					// KP_DECIMAL
// 					else if (key[4] == 'I') return 331;				// KP_DIVIDE
// 				} else if (key[3] == 'M') return 332;				// KP_MULTIPLY
// 				else if (key[3] == 'S') return 333;					// KP_SUBTRACT
// 				else if (key[3] == 'A') return 334;					// KP_ADD
// 				else if (key[3] == 'E') {
// 					if (key[4] == 'N') return 335;					// KP_ENTER
// 					else if (key[4] == 'Q') return 336;				// KP_EQUAL
// 				}
// 				break;
// 			case 'L':
// 				if (length > 4) {
// 					if (key[5] == 'S') {
// 						if (key[6] == 'H') return 340;				// LEFT_SHIFT
// 						else if (key[6] == 'U') return 343;			// LEFT_SUPER
// 					} else if (key[5] == 'C') return 341;			// LEFT_CONTROL
// 					else if (key[5] == 'A') return 342;				// LEFT_ALT
// 				} else return 263;									// LEFT
// 				break;
// 			case 'M':
// 				if (key[1] == 'O') {
// 					if (key[5] == '1') return 351;					// MOUSE1
// 					else if (key[5] == '2') return 352;				// MOUSE2
// 					else if (key[5] == '3') return 353;				// MOUSE3
// 				} else if (key[1] == 'W') {
// 					if (key[6] == 'D') return 349;					// MWHEELDOWN
// 					else if (key[6] == 'U') return 350;				// MWHEELUP
// 				} else return 348;									// MENU
// 				break;
// 			case 'N': return 282;									// NUM_LOCK
// 			case 'P':
// 				if (key[2] == 'I') return 283;						// PRINT_SCREEN
// 				else if (key[2] == 'U') return 284;					// PAUSE
// 				else if (key[2] == 'G') {
// 					if (key[5] == 'U') return 266;					// PAGE_UP
// 					else if (key[5] == 'D') return 267;				// PAGE_DOWN
// 				}
// 				break;
// 			case 'R':
// 				if (length > 5) {
// 					if (key[5] == 'S') {
// 						if (key[6] == 'H') return 344;				// RIGHT_SHIFT
// 						else if (key[6] == 'U') return 347;			// RIGHT_SUPER
// 					} else if (key[5] == 'C') return 345;			// RIGHT_CONTROL
// 					else if (key[5] == 'A') return 346;				// RIGHT_ALT
// 				} else return 262;									// RIGHT
// 				break;
// 			case 'S':
// 				if (key[1] == 'P') return 32;						// SPACE
// 				else if (key[1] == 'C') return 281;					// SCROLL_LOCK
// 				break;
// 			case 'T':
// 				if (key[1] == 'A') return 258; break;				// TAB
// 			case 'U':
// 				if (key[1] == 'P') return 265; break;				// UP
// 			}
// 		}
// 	} else if (47 < firstchar && firstchar < 58) {
// 		return firstchar;											// 0 - 9
// 	} else {
// 		switch (firstchar) {
// 			case '\'': return 39;
// 			case ',': return 44;
// 			case '-': return 45;
// 			case '.': return 46;
// 			case '/': return 47;
// 			case ';': return 59;
// 			case '=': return 61;
// 			case '[': return 91;
// 			case '\\': return 92;
// 			case ']': return 93;
// 			case '`': return 96;
// 		}
// 	}
// 	return -1;
// }

// funcPtr Command::CommandImpl::convertFunction(string func)
// {
// 	switch (func[0]) {
// 	case '+':
// 		switch(func[1]) {
// 		case 'a':
// 			if (func == "+attack")				return &Command::cmd_void;
// 			else if (func == "+attack2")			return &Command::cmd_void;
// 			break;
// 		case 'b':
// 			// if (func == "+back")					return &Player::cmd_back;
// 			break;
// 		case 'f':
// 			// if (func == "+forward")				return &Player::cmd_forward;
// 			break;
// 		case 'm':
// 			// if (func == "+moveleft")				return &Player::cmd_moveleft;
// 			// else if (func == "+moveright")		return &Player::cmd_moveright;
// 			// else if (func == "+moveup")			return &Command::cmd_void;
// 			// else if (func == "+movedown")			return &Command::cmd_void;
// 			break;
// 		case 's':
// 			if (func == "+showscores")			return &Command::cmd_void;
// 			// else if (func == "+sprint")			return &Player::cmd_sprint;
// 			break;
// 		case 'u':
// 			if (func == "+use")					return &Command::cmd_void;//cmd_use;
// 			break;
// 		}
// 		break;
// 	case 'c':
// 		if (func == "cancelselect")				return &Command::cmd_void;
// 		else if (func == "chat")					return &Command::cmd_void;
// 		else if (func == "commandmenu")			return &Command::cmd_void;
// 		else if (func == "crouch")				return &Command::cmd_void;
// 		break;
// 	case 'd':
// 		if (func == "drop")						return &Command::cmd_void;
// 		// else if (func == "debugfrustumcull")		return &FrustumCulling::cmd_debug;
// 		// else if (func == "debugnoclip")			return &Player::cmd_noclip;
// 		// else if (func == "debugorigin")			return &Player::cmd_origin;
// 		// else if (func == "debugmovezone")		return &Space::cmd_test;
// 		break;
// 	case 'e':
// 		// if (func == "exit")						return &this->cmd_exit;
// 	case 'f':
// 		if (func == "exit")						return &this->cmd_exit;
// 	case 'i':
// 		if (func == "invnext")					return &Command::cmd_void;
// 		else if (func == "invprev")				return &Command::cmd_void;
// 		break;
// 	case 'j':
// 		// if (func == "jump")						return &Player::cmd_jump;
// 		break;
// 	case 'r':
// 		if (func == "reload")					return &Command::cmd_void;
// 		break;
// 	case 's':
// 		if (func == "slot10")					return &Command::cmd_void;
// 		else if (func == "slot1")				return &Command::cmd_void;
// 		else if (func == "slot2")				return &Command::cmd_void;
// 		else if (func == "slot3")				return &Command::cmd_void;
// 		else if (func == "slot4")				return &Command::cmd_void;
// 		else if (func == "slot5")				return &Command::cmd_void;
// 		else if (func == "slot6")				return &Command::cmd_void;
// 		else if (func == "slot7")				return &Command::cmd_void;
// 		else if (func == "slot8")				return &Command::cmd_void;
// 		else if (func == "slot9")				return &Command::cmd_void;
// 		break;
// 	case 't':
// 		if (func == "toggleconsole")				return &Command::cmd_void;
// 		break;
// 	}
// 	return cmd_void;
// }
