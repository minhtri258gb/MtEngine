#ifndef __MT_TERRAIN_STATIC_H__
#define __MT_TERRAIN_STATIC_H__

#include "engine/data/HeightmapData.h"
#include "graphic/ShaderProgram.h"

namespace mt {
namespace graphic {

class TerrainStatic {
public:

	// Variables
	static ShaderProgram shader;

	// Forwards
	TerrainStatic();
	~TerrainStatic();

	void initVAO(engine::HeightmapData* data, float cellScale);
	void initTexture(std::string filepath);
	void render();
	void clear();

	// Natives

private:

	// Variables
	class TerrainStaticImpl;
	TerrainStaticImpl* impl;
};

}}

#endif
