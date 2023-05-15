#define __MT_PLUGIN_CPP__

#include <iostream>
#include <windows.h>

#include "common.h"
#include "Plugin.h"
#include "PluginBase.h"
#include "engine/exception/LoadException.h"

using namespace std;
using namespace mt;
using namespace mt::mod;

typedef PluginBase* (*CreatePluginFunc)(void);
typedef void (*DestroyPluginFunc)(void);

class mt::mod::PluginImpl
{
public:
	HINSTANCE library;
	PluginBase* plugin;
};

Plugin::Plugin()
{
	this->impl = new PluginImpl();
}

Plugin::~Plugin()
{
	delete this->impl;
}

void Plugin::load(string pluginname)
{
	HINSTANCE mod = LoadLibrary((R"(./plugins/)" + pluginname).c_str());

	if (!mod)
		throw LoadException("Library " + pluginname + " wasn't loaded successfully!", __FILE__, __LINE__);

	CreatePluginFunc createPluginFunc = (CreatePluginFunc) GetProcAddress(mod, "CreatePlugin");
	
	if (!createPluginFunc)
		throw LoadException("Library " + pluginname + " Invalid Plugin DLL: 'CreatePlugin' function must be defined.", __FILE__, __LINE__);

	PluginBase* plugin = createPluginFunc();
	if (!plugin)
		throw LoadException("Library " + pluginname + " Could not load plugin from 'CreatePlugin' function", __FILE__, __LINE__);

	this->impl->plugin = plugin;
	this->impl->library = mod;
}

void Plugin::close()
{
	DestroyPluginFunc destroyPluginFunc = (DestroyPluginFunc) GetProcAddress(this->impl->library, "DestroyPlugin");
	if (!destroyPluginFunc)
		throw LoadException("Library " + this->impl->plugin->getPluginName() + " Invalid Plugin DLL: 'DestroyPlugin' function must be defined.", __FILE__, __LINE__);
	destroyPluginFunc();

	FreeLibrary(this->impl->library);
}

PluginBase* Plugin::getObject()
{
	return this->impl->plugin;
}
