#ifndef __MT_BSP_QUAKE_MAP_H__
#define __MT_BSP_QUAKE_MAP_H__

#include "../ShaderProgram.h"

namespace mt {
namespace graphic {

class BspQuakeMap {
public:

	// Variables
	static ShaderProgram shader;

	// Constructor
	BspQuakeMap();
	~BspQuakeMap();

  // General
	void init(std::string filepath);
	void update();
	void render();

	// Natives

private:

	// Variables
	class BspQuakeMapImpl;
	BspQuakeMapImpl* impl;
};

}}

#endif
