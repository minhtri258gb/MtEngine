#ifndef __MT_COMMAND_H__
#define __MT_COMMAND_H__

namespace mt {
namespace game {

class Command
{
public:

	static void setFuncMap(std::map<std::string, function>* map);

	static void cmd_void();
	static void cmd_forward();
	static void cmd_back();
	static void cmd_left();
	static void cmd_right();
	static void cmd_debug_frustumcull();
};

}}

#endif
