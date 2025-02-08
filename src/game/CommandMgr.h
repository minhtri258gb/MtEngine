#ifndef __MT_COMMAND_MGR_H__
#define __MT_COMMAND_MGR_H__


namespace mt {
namespace game {

class CommandMgr {
public:

	static CommandMgr ins;

	// Forwards
	CommandMgr();
	~CommandMgr();

	void init();
	void update();

	// Natives
	void keyBind(std::string key, std::string func);

	// Static method
	static void cbk_keypress(int key, bool state);

private:

	// Variables
	class CommandMgrImpl;
	CommandMgrImpl* impl;

};

}}

#endif
