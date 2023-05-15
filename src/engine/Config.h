#ifndef __MT_CONFIG_H__
#define __MT_CONFIG_H__

namespace mt {
namespace engine {

class Config
{

public:

	// Variable
	static Config ins;

	// System
	std::string resource_dir;
	std::string shader_path;

	// Window
	int windowWidth;
	int windowHeight;
	std::string windowName;

	// Camera

	// Forward
	Config();
	~Config();

};

}}

#endif
