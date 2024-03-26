#define __MT_TERRAIN_PART_CPP__

#include "common.h"
#include "engine/Timer.h"
#include "../Graphic.h"
#include "TerrainQuad.h"
#include "../buffer/VertexArrayObject.h"
#include "../texture/Texture.h"
#include "TerrainPart.h"

// Import nguoc
#include "Terrain.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;

class TerrainPart::TerrainPartImpl
{
public:
	TerrainQuad* root;
	VertexArrayObject VAO;
	Texture heightMapTex;
};

TerrainPart::TerrainPart()
{
	// Implement
	impl = new TerrainPartImpl();

	// Init root
	impl->root = new TerrainQuad();
	impl->root->generateTreeEx(8, nullptr, vec2()); // TEST 8
	impl->root->generateNeighborEx(nullptr, nullptr, nullptr, nullptr);

	// Init VAO
	int maxInstance = 99999;
	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addDynamicAttribute(maxInstance, vec2());	// 0
	impl->VAO.addDynamicAttribute(maxInstance, 0);			// 1
	impl->VAO.addDynamicAttribute(maxInstance, 0);			// 2
	impl->VAO.unbind();
	impl->VAO.setCount(4); // luu 4 diem tai vs.shader

	// Init Texture
	this->heightScale = 50.0f;
	impl->heightMapTex.init("./res/terrains/static/chadvernon/texture.png");
	
}

TerrainPart::~TerrainPart()
{
	// Delete root
	delete impl->root;

	// Implement
	delete impl;
}

void TerrainPart::render()
{
	// Update Shader
	Terrain::shader.setFloat(4, this->heightScale);

	// Update Triangle
	unsigned int count = 0;
	vector<vec2> positions;
	vector<int> levels;
	vector<int> parts;
	impl->root->update();
	impl->root->getData(count, positions, levels, parts);

	if (count)
	{
		impl->heightMapTex.bind(1);

		impl->VAO.bind();
		impl->VAO.updateDynamicAttribute(0, positions);
		impl->VAO.updateDynamicAttribute(1, levels);
		impl->VAO.updateDynamicAttribute(2, parts);
		impl->VAO.drawPatchesInstance(count);
		impl->VAO.unbind();
	}
}
