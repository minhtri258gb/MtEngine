#ifndef __MT_STATIC_TERRAIN_H__
#define __MT_STATIC_TERRAIN_H__

#include "../ShaderProgram.h"

namespace mt {
namespace graphic {

class StaticTerrain {
public:

	// Variables
	static ShaderProgram shader;

	// Forwards
	StaticTerrain();
	~StaticTerrain();
	void init(std::string filepath);
	void render();

	// Natives

private:

	// Variables
	class StaticTerrainImpl;
	StaticTerrainImpl* impl;
};

}}

#endif
