#define __MT_STATIC_TERRAIN_CPP__

// #include <stb_image.h>

#include "common.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "StaticTerrain.h"

// #include "engine/file/BTFile.h"
#include "graphic/buffer/VertexArrayObject.h"
#include "graphic/texture/Texture.h"

#define MAXHEIGHTTERR 8.0f

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


class StaticTerrain::StaticTerrainImpl {
public:
	VertexArrayObject VAO;
	Texture texture;
};

ShaderProgram StaticTerrain::shader;


StaticTerrain::StaticTerrain() {
	LOG("StaticTerrain");
	try {

		// Implement
		impl = new StaticTerrainImpl();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
StaticTerrain::~StaticTerrain() {
	LOG("~StaticTerrain");

	// Implement
	delete impl;
}

void StaticTerrain::initVAO(int depth, int width, std::vector<float> heightData, float cellScale) {
	LOG("initVAO");
	try {

		// VAO
		vector<vec3> vertices;
		vector<vec2> uvs;
		vector<unsigned int> indices;
		for (int z = 0; z < depth; z++) {
			for (int x = 0; x < width; x++) {
				int index = (z*width + x);
				float height = heightData.at(index);
				float xc = x * cellScale;
				float zc = z * cellScale;

				vertices.push_back(vec3(xc, height, zc));
				uvs.push_back(vec2(x * 1.0 / width, z * 1.0 / depth));
			}
		}
		for (int z = 0; z < depth - 1; z++) {
			for (int x = 0; x < width - 1; x++) {
				indices.push_back((z) * width + (x));
				indices.push_back((z + 1) * width + (x));
				indices.push_back((z) * width + (x + 1));
				indices.push_back((z + 1) * width + (x));
				indices.push_back((z + 1) * width + (x + 1));
				indices.push_back((z) * width + (x + 1));
			}
		}

		impl->VAO.init();
		impl->VAO.bind();
		impl->VAO.addAttribute(vertices);
		impl->VAO.addAttribute(uvs);
		impl->VAO.addIndices(indices);
		impl->VAO.unbind();

		// 	vao->init(2);
		// 	vao->bindVAO();
		// 	vao->createIndexBuffer(indices);
		// 	vao->createAttribute(0, vertices);
		// 	vao->createAttribute(1, uvs);
		// 	vao->unbind();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void StaticTerrain::initTexture(string filepath) {
	LOG("initTexture");
	try {

		// Texture
		impl->texture.init(filepath);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void StaticTerrain::render() {
	LOG("render");
	try {

		shader.use();

		// Graphic::ins.wireframe(true);

		impl->texture.bind();

		impl->VAO.bind();
		impl->VAO.drawElementTriangle();
		impl->VAO.unbind();

		// Graphic::ins.wireframe(false);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void StaticTerrain::clear() {
	LOG("clear");
	try {
		// Ko có con trỏ cần giải phóng
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
