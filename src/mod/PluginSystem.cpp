#define __MT_PLUGIN_SYSTEM_CPP__

#include <windows.h>

#include "common.h"
#include "PluginSystem.h"
#include "engine/exception/LoadException.h"
#include "graphic/models/Model.h"
#include "game/entities/Entity.h"

// #define PLUGIN_PATH "../res/plugins/"
#define PLUGIN_PATH "./"

using namespace std;
using namespace mt;
using namespace mt::graphic;
using namespace mt::game;
using namespace mt::mod;

void PluginSystem::load()
{
	WIN32_FIND_DATA fileData;
	HANDLE fileHandle = FindFirstFile(R"(./plugins/*.dll)", &fileData);

	if (fileHandle == (void*)ERROR_INVALID_HANDLE || fileHandle == (void*)ERROR_FILE_NOT_FOUND) {
		cout << "Khong tim thay plugin them vao" << endl;
		return ;
	}

	do {
		Plugin* plugin = nullptr;
		try
		{
			plugin = new Plugin();
			plugin->load(string(fileData.cFileName));
			this->plugins.push_back(plugin);
		}
		catch (LoadException e)
		{
			if (plugin)
				delete plugin;
			cout << e.getMessage() << endl;
		}
	} while (FindNextFile(fileHandle, &fileData));
}

void PluginSystem::clean()
{
	for (Plugin* plugin : this->plugins)
	{
		plugin->close();
		delete plugin;
	}
}

void PluginSystem::run()
{
	this->load();
	
	for (Plugin* plugin : this->plugins)
	{
		try
		{
			PluginBase* base = dynamic_cast<PluginBase*>(plugin->getObject());
			if (!base)
				throw string("Fail to get PluginBase");

			PluginBase::PLUGIN_TYPE type = base->getPluginType();
			if (type == PluginBase::PLUGIN_TYPE::MODEL)
			{
				Model* mdl = dynamic_cast<Model*>(base);
				if (mdl)
				{
					mdl->render();
				}
			}
			else if (type == PluginBase::PLUGIN_TYPE::ENTITY)
			{
				Entity* ent = dynamic_cast<Entity*>(base);
				if (ent)
				{
					ent->update();
					ent->render();
				}
			}
			else if (type == PluginBase::PLUGIN_TYPE::MAP)
			{
			}
			else // PROCESS
			{
				base->framework();
			}
		}
		catch (string s)
		{
			cout << s << endl;
		}
		catch (...)
		{
			cout << "Object by plugin have issue" << endl;
		}
	}

	this->clean();
}
