#ifndef __MT_PLUGIN_SYSTEM_H__
#define __MT_PLUGIN_SYSTEM_H__

#include "Plugin.h"

namespace mt {
namespace mod {

class PluginSystem {

public:

	// Forward
	void load();
	void clean();
	void run();

	// Native

	// Stock

private:

	// Variable
	std::vector<Plugin*> plugins;

};

}}

#endif
