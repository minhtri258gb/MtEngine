#define __MT_TERRAIN_PART_CPP__

#include "common.h"
#include "engine/Log.h"
#include "engine/Timer.h"
#include "graphic/Graphic.h"
#include "graphic/buffer/VertexArrayObject.h"
#include "graphic/texture/Texture.h"
#include "graphic//terrain/TerrainQuad.h"
#include "TerrainPart.h"

#include "TerrainInf.h" // Inv Import

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


class TerrainPart::TerrainPartImpl {
public:
	TerrainQuad* root;
	VertexArrayObject VAO;
	Texture heightMapTex;
};


TerrainPart::TerrainPart(HeightmapData* hmData) {
	LOG("TerrainPart");
	try {

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
		vector<float> heightData = hmData->getHeightData();
		this->heightScale = hmData->getScale();
		this->heightOffset = hmData->getOffset();
		impl->heightMapTex.loadArray(&heightData[0], hmData->getWidth(), hmData->getDepth());
	}
	catch (Exception e) {
		track(e);
		if (e.getCode() == "LOAD_FAIL")
			e.setMessage("TEXTURE_NOT_FOUND", "Khong tim thay file Texture TerrainPart (res/terrains/chadvernon/heightmap.png)");
		throw e;
	}
}
TerrainPart::~TerrainPart() {
	LOG("~TerrainPart");

	// Delete root
	delete impl->root;

	// Implement
	delete impl;
}

void TerrainPart::render() {
	LOG("render");
	try {

		// Update Shader
		TerrainInf::shader.setFloat(4, this->heightScale);
		TerrainInf::shader.setFloat(5, this->heightOffset);

		// Update Triangle
		unsigned int count = 0;
		vector<vec2> positions;
		vector<int> levels;
		vector<int> parts;
		impl->root->update();
		impl->root->getData(count, positions, levels, parts);

		if (count) {
			impl->heightMapTex.bind(1);

			impl->VAO.bind();
			impl->VAO.updateDynamicAttribute(0, positions);
			impl->VAO.updateDynamicAttribute(1, levels);
			impl->VAO.updateDynamicAttribute(2, parts);
			impl->VAO.drawPatchesInstance(count);
			impl->VAO.unbind();
		}
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
