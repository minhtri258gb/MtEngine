#ifndef __MT_BSP_MAP_H__
#define __MT_BSP_MAP_H__

#include "../ShaderProgram.h"

namespace mt {
namespace graphic {

class BspMap {
public:

	// Variables
	static ShaderProgram shader;

	// Constructor
	BspMap();
	~BspMap();

  // General
	void init(std::string filepath);
	void update();
	void render();

	// Natives

private:

	// Variables
	class BspMapImpl;
	BspMapImpl* impl;
};

}}

#endif
