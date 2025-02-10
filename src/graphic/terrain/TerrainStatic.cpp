#define __MT_TERRAIN_STATIC_CPP__

// #include <stb_image.h>

#include "common.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "TerrainStatic.h"

// #include "engine/file/BTFile.h"
#include "engine/data/HeightmapData.h"
#include "graphic/buffer/VertexArrayObject.h"
#include "graphic/texture/Texture.h"

#define MAXHEIGHTTERR 8.0f

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


class TerrainStatic::TerrainStaticImpl {
public:
	VertexArrayObject VAO;
	Texture texture;
};

ShaderProgram TerrainStatic::shader;


TerrainStatic::TerrainStatic() {
	LOG("TerrainStatic");
	try {

		// Implement
		impl = new TerrainStaticImpl();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
TerrainStatic::~TerrainStatic() {
	LOG("~TerrainStatic");

	// Implement
	delete impl;
}

void TerrainStatic::initVAO(HeightmapData* data, float cellScale) {
	LOG("initVAO");
	try {

		int depth = data->getDepth();
		int width = data->getWidth();

		// VAO
		vector<vec3> vertices;
		vector<vec2> uvs;
		vector<unsigned int> indices;
		for (int z = 0; z < depth; z++) {
			for (int x = 0; x < width; x++) {
				float height = data->get(z, x);
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
void TerrainStatic::initTexture(string filepath) {
	LOG("initTexture");
	try {

		// Texture
		impl->texture.loadImage(filepath);
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
void TerrainStatic::render() {
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
void TerrainStatic::clear() {
	LOG("clear");
	try {
		// Ko có con trỏ cần giải phóng
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
