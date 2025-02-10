#define __MT_CONFIG_CPP__

#include "common.h"
#include "Config.h"
#include "engine/file/FileCFG.h"
#include "engine/utils/StringUtils.h"

using namespace std;
using namespace mt::engine;

Config Config::ins;

Config::Config() {

	// File path
	string root = "./res/";
	this->resource_dir = root;
	this->shader_path = "./shaders/";
	this->system_path = root + "system/";
	this->skybox_path = root + "skybox/";
	this->terrain_path = root + "terrains/";
	this->model_path = root + "models/";
	this->font_path = root + "fonts/";
	this->map_path = root + "maps/";

	// Load setting.ini
	FileCFG setting(this->system_path + "setting.cfg");

	// Common
	setting.select("common");
	this->DEBUG = setting.getBool("debug");

	// Window
	setting.select("window");
	this->windowWidth = setting.getInt("width");
	this->windowHeight = setting.getInt("height");
	this->windowName = "Master Engine";

	// Graphic
	setting.select("graphic");
	this->graphic_vsync = setting.getBool("vsync");
	this->graphic_terrain_wireframe = false;

	// Physic
	setting.select("physic");
	this->physic_gravity = setting.getFloat("gravity");

	// #ADD
}

Config::~Config() {
}
