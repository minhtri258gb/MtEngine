#ifndef __MT_TERRAIN_H__
#define __MT_TERRAIN_H__

// #include "../../API/OpenGL/vao/VertexBufferDynamic.h"
// #include "../../API/OpenGL/texture/Texture2DPack.h"

#include "engine/data/HeightmapData.h"
#include "graphic/ShaderProgram.h"

namespace mt {
namespace graphic {

class TerrainInf {
public:

	// Variables
	static ShaderProgram shader;
	// VertexBufferDynamic m_vb;
	// float m_maxwidth, m_maxlength;

	// Forwards
	TerrainInf();
	~TerrainInf();

	void initVAO(engine::HeightmapData* data);
	void initTexture(std::string filepath);
	void render();
	void clear();

	// void renderPre();
	// void render(vec2 origin, unsigned short level, mt::flag patch);
	// void renderPost();

	// Natives
	// unsigned short getHeightGrid(int x, int z);
	// float getHeightAny(unsigned short x, unsigned short z);

private:

	// Variable
	class TerrainInfImpl;
	TerrainInfImpl* impl;
	// Texture2DPack m_texture;
	// vector<float> heightmap, heightmapPhysic;

};

}}

#endif
