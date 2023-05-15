#ifndef __MT_TERRAIN_QUAD_H__
#define __MT_TERRAIN_QUAD_H__

namespace mt {
namespace graphic {

class TerrainQuad
{
public:

	// Variables
	unsigned char level;
	TerrainQuad* parent;
	TerrainQuad* neighbor[4];
	TerrainQuad* children[4];
	vec2 position;
    bool isRender;
    bool isVisible;

	// General
	TerrainQuad();
	~TerrainQuad();

	void generateTreeEx(unsigned char level, TerrainQuad* parent, vec2 position);
	void generateNeighborEx(TerrainQuad* n0, TerrainQuad* n1, TerrainQuad* n2, TerrainQuad* n3);
	
	void update();
	void getData(unsigned int& count, std::vector<vec2>& positions, std::vector<int>& levels, std::vector<int>& flags);

	// Natives

private:

	// Variables
	// class TerrainQuadImpl;
	// TerrainQuadImpl* impl;

};

}}

#endif
