#define __MT_STATIC_TERRAIN_CPP__

// #include <stb_image.h>

#include "common.h"
#include "../Graphic.h"
#include "StaticTerrain.h"
#include "../buffer/VertexArrayObject.h"
#include "../texture/Texture.h"
#include "engine/file/Image.h"
#include "engine/file/FileCFG.h"

// #include "../../../engine/file/BTFile.h"

#define MAXHEIGHTTERR 8.0f
#define CELLSPACE 1

using namespace std;
using namespace mt;
using namespace mt::graphic;

class StaticTerrain::StaticTerrainImpl
{
public:
	VertexArrayObject VAO;
	Texture texture;
};

ShaderProgram StaticTerrain::shader;

StaticTerrain::StaticTerrain()
{
	// Implement
	impl = new StaticTerrainImpl();
}

StaticTerrain::~StaticTerrain()
{
	// Implement
	delete impl;
}

void StaticTerrain::init(string name)
{
	// Load config
	string pathDir = "../res/terrains/static/" + name + "/";
	FileCFG* fCFG = new FileCFG(pathDir + "info.cfg");
	
	fCFG->select("terrain");
	string terrainName = fCFG->get("heightmap");
	float heightScale = fCFG->getFloat("height_scale");
	string textureFile = fCFG->get("texture");

	Image data;
	data.load(pathDir + terrainName);
	// BTFile *filebt = new BTFile("res/terrain/" + terrainName + "/heightmap.bt");

	int depth = data.getWidth();
	int width = data.getHeight();
	// float depth = filebt->getRows();
	// float width = filebt->getColumns();

	// vector<float> heightmapData;
	// heightmapData.resize((float)(depth * width), 0.0f);
	// unsigned char* pixelPtr = data.getDataPtr();
	// for (auto i = 0; i < width; i++)
	// 	for (auto j = 0; j < depth; j++)
	// 	{
	// 		heightmapData[i*depth+j] = float(*pixelPtr) / 255.0f;
	// 		pixelPtr += data.getChannel();
	// 	}

	// VAO
	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<unsigned int> indices;
	for(int z = 0; z < depth; z++)
	{
		for(int x = 0; x < width; x++)
		{
			float height = (float)data[z*width + x] / 255.0f * heightScale;
			float xc = x * CELLSPACE;
			float zc = z * CELLSPACE;

			vertices.push_back(vec3(xc, height, zc));
			uvs.push_back(vec2(x * 1.0 / width, z * 1.0 / depth));
		}
	}
	for(int z = 0; z < depth - 1; z++)
	{
		for(int x = 0; x < width - 1; x++)
		{
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

	// Texture
	impl->texture.init(pathDir + textureFile);
	

	// Clear
	delete fCFG;
}

void StaticTerrain::render()
{
	shader.use();

	// Graphic::ins.wireframe(true);

	impl->texture.bind();

	impl->VAO.bind();
	impl->VAO.drawElementTriangle();
	impl->VAO.unbind();

	// Graphic::ins.wireframe(false);
}
