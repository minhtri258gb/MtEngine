#ifndef __MT_COMMAND_H__
#define __MT_COMMAND_H__

namespace mt {
namespace game {

class Command {
public:

	static void setFuncMap(std::map<std::string, function>* map);

	// Common
	static void cmd_void();
	static void cmd_exit();
	static void cmd_cursor();

	// Debug
	static void cmd_debug_frustumcull();

	// UI
	static void cmd_console();
	static void cmd_pause();
	static void cmd_help();
	static void cmd_setting();
	static void cmd_monitor();

	// Player
	static void cmd_forward();
	static void cmd_back();
	static void cmd_left();
	static void cmd_right();
};

}}

#endif
