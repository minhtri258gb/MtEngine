#ifndef __MT_BSP_SOURCE_MAP_H__
#define __MT_BSP_SOURCE_MAP_H__

#include "../ShaderProgram.h"

namespace mt {
namespace graphic {

class BspSourceMap {
public:

	// Variables
	static ShaderProgram shader;

	// Constructor
	BspSourceMap();
	~BspSourceMap();

  // General
	void init(std::string filepath);
	void update();
	void render();

	// Natives

private:

	// Variables
	class BspSourceMapImpl;
	BspSourceMapImpl* impl;
};

}}

#endif
