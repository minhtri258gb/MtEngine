#define __MT_TERRAIN_CPP__

#define FLAG_WIREFRAME 1
#define CELLSPACE (1<<8)

#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "graphic/Graphic.h"
#include "Terrain.h"

#include "engine/file/FileCFG.h"
#include "engine/file/Image.h"
#include "engine/random/PerlinNoise.h"
#include "graphic/buffer/VertexArrayObject.h"
#include "graphic/texture/Texture.h"
#include "graphic/terrain/TerrainPart.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


class Terrain::TerrainImpl {
public:
	array<TerrainPart*, 61> parts;
	Texture texture;
	PerlinNoise noise;
};

ShaderProgram Terrain::shader;


Terrain::Terrain() {
	LOG("Terrain");
	try {

		// Implement
		impl = new TerrainImpl();

		// m_maxwidth = 0;
		// m_maxlength = 0;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}
Terrain::~Terrain() {
	LOG("~Terrain");

	// Implement
	delete impl;
}

void Terrain::init(string name) {
	LOG("init");
	try {

		// Data
		FileCFG fCFG(Config::ins.terrain_path + name + "/info.cfg");

		// Doc du lieu tu file cau hinh
		enum eTerrainSizeStyle {
			VerySmall = 1,
			Small = 9,
			Medium = 21,
			Large = 37,
			VeryLarge = 61
		};
		eTerrainSizeStyle size = VerySmall;

		for (int i=0; i<size; i++)
			impl->parts[i] = new TerrainPart();

		// TODO ...

		// Data
		// Image data;
		// data.load("./res/textures/heightmap/57fd738417ea37bf5af6c2493fd8d54644f5a45a.jpeg");
		// BTFile fBT("res/terrain/" + name + "/heightmap.bt");

		// int depth = data.getWidth();
		// int width = data.getHeight();
		// float depth = fBT.getRows();
		// float width = fBT.getColumns();

		// Find
		// int maxsize = depth > width ? depth : width;
		// short hsize = 1;
		// while(maxsize > (1 << hsize))
		// 	hsize++;

		// m_maxwidth = depth;
		// m_maxlength = width;

			// for (int z=0; z<depth; z++)
		// 	for (int x=0; x<width; x++)
		// 	{
		// 		float h = fBT.getData(depth - z - 1, x);
		// 		heightmap.push_back(h);
		// 		heightmapPhysic.push_back(h - 128.0f);
		// 	}

		// Import to world
		// g_pSystem->world.addTerrain(width, depth, &heightmapPhysic[0], CELLSPACE);

		// Vertex buffer
		// m_vb.init(2);
		// m_vb.bind();
		// m_vb.storaIndex(24);
		// m_vb.storaAttribute(0, 3, 9);
		// m_vb.storaAttribute(1, 2, 9);
		// m_vb.unbind();

	// 	// Texture
		// m_texture.loadAdd("res/terrain/" + name + "/bgTexture.tga");
	// 	m_texture.loadAdd("res/terrain/" + name + "/texDetailR.tga");
	// 	m_texture.loadAdd("res/terrain/" + name + "/texDetailG.tga");
	// 	m_texture.loadAdd("res/terrain/" + name + "/texDetailB.tga");
	// 	m_texture.loadAdd("res/terrain/" + name + "/texDetailA.tga");
	// 	m_texture.loadAdd("res/terrain/" + name + "/texPartR.tga");
	// 	m_texture.loadAdd("res/terrain/" + name + "/texPartG.tga");
	// 	m_texture.loadAdd("res/terrain/" + name + "/texPartB.tga");
	// 	m_texture.loadAdd("res/terrain/" + name + "/texPartA.tga");

		// Init Texture
		impl->texture.init("./res/terrains/static/chadvernon/texture.png");
	}
	catch (Exception e) {
		if (e.getCode() == "LOAD_FAIL") {
			throw error("CONFIG_NOT_FOUND", "Khong tim thay file Config Terrain ("+name+")");
		}
		else {
			track(e);
			throw e;
		}
	}
}
void Terrain::render() {
	LOG("init");
	try {

		Terrain::shader.use();

		Graphic::ins.setPatchParameter(4);

		#if FLAG_WIREFRAME
		Graphic::ins.wireframe(true);
		#endif

		impl->texture.bind(0);

		for (unsigned short i=0; i<61; i++) {
			TerrainPart* part = impl->parts[i];
			if (part)
				part->render();
		}

		#if FLAG_WIREFRAME
		Graphic::ins.wireframe(false);
		#endif
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

// void Terrain::renderPre()
// {
// 	shader->use();
// 	shader->loadViewMat();
// 	m_texture.bind();
// }

/*
* Quad info:
	1	8	7
	2	0	6
	3	4	5

* Coord
	00	10
	01	11
*/
// void Terrain::render(vec2 origin, unsigned short level, mt::flag patch)
// {
// 	// Origin
// 	int halfsize = 1 << (level-1);
// 	int minX = origin.x, minZ = origin.y;
// 	int midX = minX+halfsize, midZ = minZ+halfsize;
// 	int maxX = midX+halfsize, maxZ = midZ+halfsize;

// 	halfsize *= CELLSPACE;
// 	int minXS = minX*CELLSPACE, minZS = minZ*CELLSPACE;
// 	int midXS = minXS+halfsize, midZS = minZS+halfsize;
// 	int maxXS = midXS+halfsize, maxZS = midZS+halfsize;

// 	float maxwidth = g_pSpace->terrain.m_maxlength;
// 	float maxdepth = g_pSpace->terrain.m_maxwidth;
// 	float minV, minU, midV, midU, maxV, maxU;
// 	minV = minX/maxwidth; minU = minZ/maxdepth;
// 	midV = midX/maxwidth; midU = midZ/maxdepth;
// 	maxV = maxX/maxwidth; maxU = maxZ/maxdepth;

// 	// Build vertices
// 	vector<vec3> vertices;
// 	vertices.push_back(vec3(midXS, g_pSpace->terrain.getHeightGrid(midX,midZ), midZS));
// 	vertices.push_back(vec3(minXS, g_pSpace->terrain.getHeightGrid(minX,minZ), minZS));
// 	vertices.push_back(vec3(minXS, g_pSpace->terrain.getHeightGrid(minX,midZ), midZS));
// 	vertices.push_back(vec3(minXS, g_pSpace->terrain.getHeightGrid(minX,maxZ), maxZS));
// 	vertices.push_back(vec3(midXS, g_pSpace->terrain.getHeightGrid(midX,maxZ), maxZS));
// 	vertices.push_back(vec3(maxXS, g_pSpace->terrain.getHeightGrid(maxX,maxZ), maxZS));
// 	vertices.push_back(vec3(maxXS, g_pSpace->terrain.getHeightGrid(maxX,midZ), midZS));
// 	vertices.push_back(vec3(maxXS, g_pSpace->terrain.getHeightGrid(maxX,minZ), minZS));
// 	vertices.push_back(vec3(midXS, g_pSpace->terrain.getHeightGrid(midX,minZ), minZS));

// 	// Build texture coord
// 	vector<vec2> uvs;

// 	uvs.push_back(vec2(midV, midU));
// 	uvs.push_back(vec2(minV, minU));
// 	uvs.push_back(vec2(minV, midU));
// 	uvs.push_back(vec2(minV, maxU));
// 	uvs.push_back(vec2(midV, maxU));
// 	uvs.push_back(vec2(maxV, maxU));
// 	uvs.push_back(vec2(maxV, midU));
// 	uvs.push_back(vec2(maxV, minU));
// 	uvs.push_back(vec2(midV, minU));

// 	// Build indices
// 	vector<unsigned int> indices;

// 	if (patch.check(1)) {
// 		indices.push_back(0); indices.push_back(1); indices.push_back(3);
// 	} else {
// 		indices.push_back(0); indices.push_back(1); indices.push_back(2);
// 		indices.push_back(0); indices.push_back(2); indices.push_back(3);
// 	}
// 	if (patch.check(3)) {
// 		indices.push_back(0); indices.push_back(3); indices.push_back(5);
// 	} else {
// 		indices.push_back(0); indices.push_back(3); indices.push_back(4);
// 		indices.push_back(0); indices.push_back(4); indices.push_back(5);
// 	}
// 	if (patch.check(2)) {
// 		indices.push_back(0); indices.push_back(5); indices.push_back(7);
// 	} else {
// 		indices.push_back(0); indices.push_back(5); indices.push_back(6);
// 		indices.push_back(0); indices.push_back(6); indices.push_back(7);
// 	}
// 	if (patch.check(0)) {
// 		indices.push_back(0); indices.push_back(7); indices.push_back(1);
// 	} else {
// 		indices.push_back(0); indices.push_back(7); indices.push_back(8);
// 		indices.push_back(0); indices.push_back(8); indices.push_back(1);
// 	}

// 	shader->loadLevelQuad(level);

// 	m_vb.bind();
// 	m_vb.updateAttribute(0, vertices);
// 	m_vb.updateAttribute(1, uvs);
// 	m_vb.updateIndex(indices);
// 	m_vb.draw();
// 	m_vb.unbind();
// }

// void Terrain::renderPost()
// {
// #if WIREFRAME
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// #endif
// }

// unsigned short Terrain::getHeightGrid(int x, int z)
// {
// 	int hmax = (1 << 8); // #LEVEL8
// 	if (x >= hmax || z >= hmax)
// 		return 0;
// 	return heightmap[(z) * hmax + (x)];
// }

// float Terrain::getHeightAny(unsigned short x, unsigned short z)
// {
// 	int hmax = (1 << 8); // #LEVEL8

// 	float xC = (x % CELLSPACE)*1.0f/CELLSPACE;
// 	float zC = (z % CELLSPACE)*1.0f/CELLSPACE;
// 	float answer;

// 	x /= CELLSPACE;
// 	z /= CELLSPACE;

// 	if (x >= hmax || z >= hmax || x < 0 || z < 0) {
// 		return 0;
// 	}

// 	if (xC <= (1-zC))
// 		answer = (1-xC-zC)*heightmap[z*hmax+x] + xC*heightmap[z*hmax+x+1] + zC*heightmap[(z+1)*hmax+x];
// 	else
// 		answer = (1-zC)*heightmap[z*hmax+x+1] + (xC+zC-1)*heightmap[(z+1)*hmax+x+1] + (1-xC)*heightmap[(z+1)*hmax+x];

// 	return answer;
// }
