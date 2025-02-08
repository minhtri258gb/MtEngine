#ifndef __MT_CONFIG_H__
#define __MT_CONFIG_H__

namespace mt {
namespace engine {

class Config {

public:

	// Variable
	static Config ins;

	// Common
	bool DEBUG;

	// System
	std::string resource_dir;
	std::string system_path;
	std::string shader_path;
	std::string skybox_path;
	std::string terrain_path;
	std::string model_path;
	std::string font_path;
	std::string map_path;

	// Window
	int windowWidth;
	int windowHeight;
	std::string windowName;

	// Graphic
	bool graphic_vsync;

	// Physic
	float physic_gravity;

	// Forward
	Config();
	~Config();

};

}}

#endif
