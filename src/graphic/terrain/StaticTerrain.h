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

	void initVAO(int depth, int width, std::vector<float> heightData, float cellScale);
	void initTexture(std::string filepath);
	void render();
	void clear();

	// Natives

private:

	// Variables
	class StaticTerrainImpl;
	StaticTerrainImpl* impl;
};

}}

#endif
