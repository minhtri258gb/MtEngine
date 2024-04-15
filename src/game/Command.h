#ifndef __MT_COMMAND_H__
#define __MT_COMMAND_H__

namespace mt {
namespace game {

class Command
{
public:

	static void setFuncMap(std::map<std::string, function>* map);

	static void cmd_void();
	static void cmd_debug_frustumcull();
};

}}

#endif
