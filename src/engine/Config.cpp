#define __MT_CONFIG_CPP__

#include "common.h"
#include "Config.h"
#include "engine/file/FileINI.h"
#include "engine/utils/StringUtils.h"

using namespace std;
using namespace mt::engine;

Config Config::ins;

Config::Config()
{
	// Load setting.ini
	FileINI setting;
	setting.load("./res/setting.ini");

	// File path
	this->resource_dir = "./res/";
	this->shader_path = this->resource_dir + "shaders/";
	this->skybox_path = this->resource_dir + "skybox/";

	// Window
	this->windowWidth = StringUtils::parseInt(setting.get("window","width"));
	this->windowHeight = StringUtils::parseInt(setting.get("window","height"));
	this->windowName = "Master Engine";

	// Camera
	
	// #ADD
}

Config::~Config()
{
}
