#ifndef __MT_COMMAND_H__
#define __MT_COMMAND_H__

namespace mt {
namespace game {

class Command
{
public:

	// Variables
	static Command ins;

	// Forwards
	Command();
	~Command();

	// Natives

private:

	// Variables
	class CommandImpl;
	CommandImpl* impl;

};

}}

#endif
