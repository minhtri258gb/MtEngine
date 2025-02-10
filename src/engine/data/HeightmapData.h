#ifndef __MT_HEIGHTMAP_DATA_H__
#define __MT_HEIGHTMAP_DATA_H__

#include "engine/random/PerlinNoise.h"

namespace mt {
namespace engine {

class HeightmapData {
public:

	// Forwards
	HeightmapData();
	~HeightmapData();

	void loadArray(float* pData, int depth, int width, vec2 range, float scale);
	void loadImage(std::string filepath, float scale);
	void loadNoise(PerlinNoise& noise, int depth, int width, float scale);

	// Natives
	float get(int z, int x);
	float getDepth();
	float getWidth();
	float getScale();
	float getOffset();
	std::vector<float> getHeightData();

private:

	// Variables
	class HeightmapDataImpl;
	HeightmapDataImpl* impl;
};

}}

#endif
