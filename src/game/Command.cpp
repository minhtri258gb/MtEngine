#define __MT_COMMAND_CPP__

#include "common.h"

#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "graphic/ui/Panel.h"
#include "game/Game.h"
#include "Command.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::game;


void Command::setFuncMap(std::map<std::string, function>* map) {
	LOG("setFuncMap");
	try {
		map->insert({"+forward", &Command::cmd_forward});
		map->insert({"+back", &Command::cmd_back});
		map->insert({"+left", &Command::cmd_left});
		map->insert({"+right", &Command::cmd_right});
		map->insert({"+showscores", &Command::cmd_void});
		map->insert({"+attack", &Command::cmd_void});
		map->insert({"jump", &Command::cmd_void});
		map->insert({"+moveup", &Command::cmd_void});
		map->insert({"buyammo1", &Command::cmd_void});
		map->insert({"buyammo2", &Command::cmd_void});
		map->insert({"+movedown", &Command::cmd_void});
		map->insert({"slot10", &Command::cmd_void});
		map->insert({"slot1", &Command::cmd_void});
		map->insert({"slot2", &Command::cmd_void});
		map->insert({"slot3", &Command::cmd_void});
		map->insert({"slot4", &Command::cmd_void});
		map->insert({"slot5", &Command::cmd_void});
		map->insert({"slot6", &Command::cmd_void});
		map->insert({"slot7", &Command::cmd_void});
		map->insert({"slot8", &Command::cmd_void});
		map->insert({"slot9", &Command::cmd_void});
		map->insert({"+mlook", &Command::cmd_void});
		map->insert({"invprev", &Command::cmd_void});
		map->insert({"invnext", &Command::cmd_void});
		map->insert({"+moveleft", &Command::cmd_void});
		map->insert({"buy", &Command::cmd_void});
		map->insert({"radio3", &Command::cmd_void});
		map->insert({"+moveright", &Command::cmd_void});
		map->insert({"+use", &Command::cmd_void});
		map->insert({"drop", &Command::cmd_void});
		map->insert({"+commandmenu", &Command::cmd_void});
		map->insert({"cheer", &Command::cmd_void});
		map->insert({"+voicerecord", &Command::cmd_void});
		map->insert({"showbriefing", &Command::cmd_void});
		map->insert({"chooseteam", &Command::cmd_void});
		map->insert({"nightvision", &Command::cmd_void});
		map->insert({"buyequip", &Command::cmd_void});
		map->insert({"lastinv", &Command::cmd_void});
		map->insert({"+reload", &Command::cmd_void});
		map->insert({"+back", &Command::cmd_void});
		map->insert({"messagemode2", &Command::cmd_void});
		map->insert({"radio2", &Command::cmd_void});
		map->insert({"messagemode", &Command::cmd_void});
		map->insert({"radio1", &Command::cmd_void});
		map->insert({"+duck", &Command::cmd_void});
		map->insert({"+sprint", &Command::cmd_void});
		map->insert({"debug_origin", &Command::cmd_void});
		map->insert({"debug_noclip", &Command::cmd_void});
		map->insert({"debug_frustumcull", &Command::cmd_debug_frustumcull});
		map->insert({"debug_movezone", &Command::cmd_void});
		map->insert({"invnext", &Command::cmd_void});
		map->insert({"invprev", &Command::cmd_void});
		map->insert({"+attack", &Command::cmd_void});
		map->insert({"+attack2", &Command::cmd_void});
		map->insert({"cursor", &Command::cmd_cursor});

		// Common
		map->insert({"exit", &Command::cmd_exit});

		// UI
		map->insert({"console", &Command::cmd_console});
		map->insert({"pause", &Command::cmd_pause});
		map->insert({"help", &Command::cmd_help});
		map->insert({"setting", &Command::cmd_setting});
		map->insert({"monitor", &Command::cmd_monitor});
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

// Common
void Command::cmd_void() { } // Do Notthing
void Command::cmd_exit() {
	LOG("cmd_exit");
	try {
		Game::ins.exit();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Command::cmd_cursor() {
	LOG("cmd_cursor");
	try {
		bool state = Graphic::ins.isShowCursor();
		Graphic::ins.showCursor(!state);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

// Debug
void Command::cmd_debug_frustumcull() {
	Graphic::ins.camera.frustumCulling.debug();
}

// UI
void Command::cmd_console() {
	LOG("cmd_console");
	try {
		Game::ins.screen.togglePanel("console");
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Command::cmd_pause() {
	LOG("cmd_pause");
	try {

		// Toggle Panel
		bool isShow = Game::ins.screen.togglePanel("menu");

		// Show/Hide cursor
		Graphic::ins.showCursor(isShow);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Command::cmd_help() {
	LOG("cmd_help");
	try {

		// Toggle Panel
		bool isShow = Game::ins.screen.togglePanel("help");

		// Show/Hide cursor
		Graphic::ins.showCursor(isShow);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Command::cmd_setting() {
	LOG("cmd_setting");
	try {

		// Toggle Panel
		bool isShow = Game::ins.screen.togglePanel("setting");

		// Show/Hide cursor
		Graphic::ins.showCursor(isShow);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void Command::cmd_monitor() {
	LOG("cmd_monitor");
	try {

		// Toggle Panel
		bool isShow = Game::ins.screen.togglePanel("monitor");

		// Show/Hide cursor
		Graphic::ins.showCursor(isShow);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

// Player
void Command::cmd_forward() {
	Game::ins.map->player.movement(1);
}
void Command::cmd_back() {
	Game::ins.map->player.movement(2);
}
void Command::cmd_left() {
	Game::ins.map->player.movement(3);
}
void Command::cmd_right() {
	Game::ins.map->player.movement(4);
}
