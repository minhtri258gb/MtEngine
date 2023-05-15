#ifndef __MT_TERRAIN_PART_H__
#define __MT_TERRAIN_PART_H__

namespace mt {
namespace graphic {

class TerrainPart
{
public:

	// Variables

	// Forwards
	TerrainPart();
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
