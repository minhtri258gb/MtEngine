#ifndef __MT_TERRAIN_PART_H__
#define __MT_TERRAIN_PART_H__

#include "engine/data/HeightmapData.h"

namespace mt {
namespace graphic {

class TerrainPart {
public:

	// Variables
	float heightScale;
	float heightOffset;

	// Forwards
	TerrainPart(engine::HeightmapData* data);
	~TerrainPart();

	void render();

	// Natives

private:

	// Variables
	class TerrainPartImpl;
	TerrainPartImpl* impl;
};

}}

#endif
