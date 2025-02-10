#define __MT_BSP_SOURCE_MAP_CPP__

#define HEADER_LUMPS 64
#define VBSP_HEADER (('P'<<24) + ('S' << 16) + ('B' << 8) + 'V')

#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"
#include "engine/math/Math.h"
#include "graphic/Graphic.h"
#include "BspSourceMap.h"

#include "graphic/buffer/VertexArrayObject.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;


class bsp {
public:
	bsp (const char* fp) {

		std::cout << "Opening file...";
		map.open (fp, std::ios::binary);
		std::cout << "done.\n";

		std::cout << "Reading header...";
		map.seekg(0);
		map.read ((char*)&header, sizeof (Header));
		std::cout << "done.\n";

		if (header.magic == VBSP_HEADER)
			std::cout << "File matches VBSP.\n";

		if (header.version == 0x17)
			std::cout << "File matches Dota 2 BSP version.\n";
		else
			std::cout << "BSP is not Dota 2 BSP.\n";

		std::cout << "Verifying lumps...\n";
		for (int x = 0; x < 64; x++) {
			if (header.lumps[x].length == 0)
				std::cout << "Lump " << x << " is not included in this file.\n";
		}

		std::cout << "Reading node lump...";
		readLump(map, nodes, LUMP_NODES);
		std::cout << "done.\n";

		std::cout << "Reading leaf lump...";
		readLump(map, leafs, LUMP_LEAFS);
		std::cout << "done.\n";

		std::cout << "Reading face lump...";
		readLump(map, faces, LUMP_FACES);
		std::cout << "done.\n";

		std::cout << "Reading edge lump...";
		readLump(map, edges, LUMP_EDGES);
		std::cout << "done.\n";

		std::cout << "Reading surfedge lump...";
		readLump(map, SurfEdges, LUMP_SURFEDGES);
		std::cout << "done.\n";

		std::cout << "Creating leafface lump...";\
		readLump(map, leafFaces, LUMP_LEAFFACES);
		std::cout << "done.\n";

		std::cout << "Reading vertex lump...";
		readLump(map, vertices, LUMP_VERTICES);
		std::cout << "done.\n";

		std::cout << "Reading plane lump...";
		readLump(map, planes, LUMP_PLANES);
		std::cout << "done.\n";

		map.close();

		mapNormals.resize (vertices.size(), Vertex(0,0,0));
	}

	void LoadMapDetails(glm::vec3 pos) {

		int curLeaf = WalkBSPTree (pos, 0);
		std::cout << "Current leaf: " << curLeaf;

		ComputeBSP (0, curLeaf, pos);
	}

	enum lumpTypes {LUMP_ENTITIES = 0, LUMP_PLANES, LUMP_TEXDATA, LUMP_VERTICES, LUMP_VISIBILITY, LUMP_NODES, LUMP_TEXINFO, LUMP_FACES, LUMP_LIGHTING, LUMP_OCCLUSION, LUMP_LEAFS, LUMP_FACEIDS, LUMP_EDGES, LUMP_SURFEDGES, LUMP_MODELS, LUMP_WORLDLIGHTS,
				LUMP_LEAFFACES, LUMP_LEAFBRUSHES, LUMP_BRUSHES, LUMP_BRUSHSIDES, LUMP_AREAS, LUMP_AREAPORTALS, LUMP_PORTALS, LUMP_UNUSED0, LUMP_PROPCOLLISION, LUMP_CLUSTERS, LUMP_UNUSED1, LUMP_PROPHULLS, LUMP_PORTALVERTS, LUMP_UNUSED2,
				LUMP_PROPTRIS, LUMP_DISPINFO, LUMP_ORIGINALFACES, LUMP_PHYSDISP, LUMP_PHYSCOLLIDE, LUMP_VERTNORMALS, LUMP_VERTNORMALINDICES, LUMP_DISP_LIGHTMAP_ALPHAS, LUMP_DISP_VERTS, LUMP_DISP_LIGHTMAP_SAMPLE_POSITIONS,
				LUMP_GAME_LUMP, LUMP_LEAFWATERDATA, LUMP_PRIMITIVES, LUMP_PRIMVERTS, LUMP_PRIMINDICES, LUMP_PAKFILE, LUMP_CLIPPORTALVERTS, LUMP_CUBEMAPS, LUMP_TEXDATA_STRING_DATA, LUMP_TEXDATA_STRING_TABLE, LUMP_OVERLAYS, LUMP_LEAFMINDISTTOWATER,
				LUMP_FACE_MACRO_TEXTURE_INFO, LUMP_DISP_TRIS, LUMP_PHYSCOLLIDESURFACE, LUMP_PROP_BLOB, LUMP_WATEROVERLAYS, LUMP_LIGHTMAPPAGES, LUMP_LEAF_AMBIENT_INDEX_HDR, LUMP_LIGHTMAPPAGEINFOS, LUMP_LEAF_AMBIENT_INDEX, LUMP_LIGHTING_HDR,
				LUMP_WORLDLIGHTS_HDR, LUMP_LEAF_AMBIENT_LIGHTING_HDR, LUMP_LEAF_AMBIENT_LIGHTING, LUMP_XZIPPAKFILE, LUMP_FACES_HDR, LUMP_MAP_FLAGS, LUMP_OVERLAY_FADES, LUMP_OVERLAY_SYSTEM_LEVELS, LUMP_PHYSLEVEL, LUMP_DISP_MULTIBLEND};

	// TODO: Major cleanup
	///////////////////////////
	// TODO ASAP: Make naming more consistent, everything is all over the place right now
	///////////////////////////

	// Contains the info of every lump (offset from beginning of file, length of lump, version (usually 0), and identification (usually 0)
	struct lumpInfo {
		int offset;
		int length;
		int version;
		char ident[4];
	};

	// Main header struct
	struct Header {
		int magic;
		int version;
		lumpInfo lumps[HEADER_LUMPS];
		int revision;
	};

	// Vertex struct
	struct Vertex {
		float x, y, z;

		// cleaner usage of verts
		Vertex pos() {
			return Vertex (x, y, z);
		};

		Vertex (float a, float b, float c) {
			x = a;
			y = b;
			z = c;
		};

		Vertex (){};
	};
	std::vector <Vertex> vertices; // map verts

	struct Plane {
		Vertex normal;
		float distance;
		int type;
	};
	std::vector <Vertex> mapNormals; // map normals

	struct Node {
		int planeIndex;
		int children[2];
		short mins[3];
		short maxs[3];
		unsigned short faceIndex;
		unsigned short numFaces;
		short area;
		short padding;
	};
	std::vector <Node> nodes;

	struct Leaf {
		int contents;
		short cluster;
		short area:9; // use only 9 bits
		short flags:7;
		short mins[3];
		short maxs[3];
		unsigned short firstLeafFace;
		unsigned short numLeafFaces;
		unsigned short firstLeafBrush;
		unsigned short numLeafBrushes;
		short leafWaterDataID;

	};
	std::vector <Leaf> leafs;
	std::vector <unsigned short> leafFaces;

	struct Face {
		unsigned short planeIndex;
		unsigned __int8 side; // visual c++ stuffs, change it later
		unsigned __int8 onNode;
		int firstEdge;
		short numEdges;
		short texInfo;
		short dispInfo;
		short surfaceFogVolumeID;
		unsigned __int8 styles[4];
		int lightOfs;
		float area;
		int lightmapTextureMinsInLuxels[2];
		int lightmapTextureSizeInLuxels[2];
		int origFace;
		unsigned short numPrims;
		unsigned short firstPrimID;
		unsigned int smoothingGroups;
	};
	std::vector <Face> faces;

	struct Edge {
		unsigned short vert[2];
	};
	std::vector <Edge> edges;

	std::vector <int> SurfEdges;

	std::vector <Plane> planes;

	std::vector <GLuint> indices; // Final index vector

private:
	std::ifstream map;
	Header header;

	//http://sourceforge.net/p/hlbsp/code/HEAD/tree/hlbsp.cpp#l897
	// a lot of the code right here is from ^, make own code once I get everything solid
	int WalkBSPTree (glm::vec3 pos, int node)
	{
		for (int x = 0; x < 2; x++) {
			if (nodes[node].children[x] >= 0) { // node
				if (PointIsInside (pos, nodes[nodes[node].children[x]].mins, nodes[nodes[node].children[x]].maxs))
					return WalkBSPTree (pos, nodes[node].children[x]);
			}
			else if (~nodes[node].children[x] != 0) { // NOT x = -x - 1, so this an index for the leaves
				if (PointIsInside (pos, leafs[~(nodes[node].children[x])].mins, leafs[~(nodes[node].children[x])].maxs))
					return ~nodes[node].children[x];
			}
		}

		return -1;
	}

	bool PointIsInside (glm::vec3 pos, short min[3], short max[3]) {
		if ((min[0] <= pos.x && pos.x <= max[0] &&
					min[1] <= pos.y && pos.y <= max[1] &&
					min[2] <= pos.z && pos.z <= max[2]) ||
				(min[0] >= pos.x && pos.x >= max[0] &&
					min[1] >= pos.y && pos.y >= max[1] &&
					min[2] >= pos.z && pos.z >= max[2]))
			return true;
		else
			return false;
	}

	void ComputeBSP (int node, int leaf, glm::vec3 pos) { // my mind i dont even
		if (node < 0) {
			if (node == -1)
				return;

			RenderLeaf (~node);
			return;
		}

		float location;

		if (planes[nodes[node].planeIndex].type == 0) // plane x
			location = pos.x - planes[nodes[node].planeIndex].distance;
		else if (planes[nodes[node].planeIndex].type == 1) // plane y
			location = pos.y - planes[nodes[node].planeIndex].distance;
		else if (planes[nodes[node].planeIndex].type == 2) // plane z
			location = pos.z - planes[nodes[node].planeIndex].distance;
		else
			location = dotProduct (planes[nodes[node].planeIndex].normal, pos) - planes[nodes[node].planeIndex].distance;

		if (location > 0) {
			ComputeBSP (nodes[node].children[1], leaf, pos);
			ComputeBSP (nodes[node].children[0], leaf, pos);
		}
		else {
			ComputeBSP (nodes[node].children[0], leaf, pos);
			ComputeBSP (nodes[node].children[1], leaf, pos);
		}
	}

	void RenderLeaf (int leaf) { // loadleaf()
		for (int x = 0; x < leafs[leaf].numLeafFaces; x++)
			RenderFace (leafFaces[leafs[leaf].firstLeafFace + x]);
	}

	void RenderFace (int face) { // loadface()
		int hub, firstPoint, newPoint; // key indices for each face
		// 8 and 9, 20 and 21, 12, and 13, 24 and 25, 38 and 39,
		for (int x = 0; x < faces[face].numEdges; x++) { // loop through every single edge in a face, this will end up making a triangle fan
			int EdgeIndex = SurfEdges[faces[face].firstEdge + x]; // Edge index
			EdgeIndex = std::abs (EdgeIndex); // don't want to be accessing using negatives

			if (x == 0)
				hub = edges[EdgeIndex].vert[0]; // if this is the first run through the first vertex is the "hub" index that all of the triangles in the plane will refer to

			firstPoint = edges[EdgeIndex].vert[0]; // the second point after the hub
			newPoint = edges[EdgeIndex].vert[1]; // last point to create a full triangle

			/*still trying to fix normals*/
			mapNormals[hub] = planes[faces[face].planeIndex].normal;
			mapNormals[firstPoint] = planes[faces[face].planeIndex].normal;
			mapNormals[newPoint] = planes[faces[face].planeIndex].normal;

			// push back every single index
			indices.push_back (hub);
			indices.push_back (firstPoint);
			indices.push_back (newPoint);
		}

		indices.push_back(UINT_MAX); // once we are done rendering our plane we put in our primitive restart index to start a new plane
	}

	float dotProduct (Vertex a, glm::vec3 b) {
		return  (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	bool loadHeader();

	template <typename T> void readLump (std::ifstream& map, std::vector<T>& elements, unsigned int index) {
		elements.clear();

		if (header.lumps[index].length == 0) // lump doesn't exist
			return;

		map.seekg (header.lumps[index].offset);

		for (long long unsigned int x = 0; x < header.lumps[index].length / sizeof(T); x++) {
			T element;
			map.read ((char*)&element, sizeof(T));
			elements.push_back (element);
		}
	}

	// ^^^ thank you layla for showing this ^^^
};

// ===========

ShaderProgram BspSourceMap::shader;


class BspSourceMap::BspSourceMapImpl {
public:
	bsp* map;
	VertexArrayObject VAO;
};

BspSourceMap::BspSourceMap() {
	// Implement
	impl = new BspSourceMapImpl();
}

BspSourceMap::~BspSourceMap() {
	// Component
	delete impl->map;

	// Implement
	delete impl;
}

void BspSourceMap::init(string name) {
	// Load
	// impl->map = new bsp("./res/bsp/de_dust2.bsp");
	// impl->map = new bsp("./res/bsp/css_cs_deadhouse_1.0/cs_deadhouse.bsp");
	impl->map = new bsp("./res/bsp/source/CS_Sklad_Top-X/maps/cs_sklad_top-x.bsp");

	vec3 camPos = Graphic::ins.camera.position;
	glm::vec3 camPos2(camPos.x, camPos.y, camPos.z);
	impl->map->LoadMapDetails(camPos2);

	vector<vec3> vertices;
	for (long long unsigned int i=0; i<impl->map->vertices.size(); i++) {
		bsp::Vertex v = impl->map->vertices[i];
		vertices.push_back(vec3(v.x, v.y, v.z));
	}

	vector<vec3> normals;
	for (long long unsigned int i=0; i<impl->map->mapNormals.size(); i++) {
		bsp::Vertex n = impl->map->mapNormals[i];
		normals.push_back(vec3(n.x, n.y, n.z));
	}

	vector<unsigned int> indices;
	for (long long unsigned int i=0; i<impl->map->indices.size(); i++) {
		GLuint index = impl->map->indices[i];
		indices.push_back((unsigned int)index);
	}


	impl->VAO.init();
	impl->VAO.bind();
	impl->VAO.addAttribute(vertices);
	impl->VAO.addAttribute(normals);
	impl->VAO.addIndices(indices);
	impl->VAO.unbind();

	glEnable (GL_PRIMITIVE_RESTART); // experimental
	glPrimitiveRestartIndex (UINT_MAX);
}

void BspSourceMap::update() {
}

void BspSourceMap::render() {

	this->shader.use();

	// Model Mat
	mat4 modelMat;
	modelMat.rotate(quat(Math::toRadian(-90.0), vec3 (1,0,0)));
	modelMat.scale(0.1f);
	this->shader.setMat4(2, modelMat);

	// Graphic::ins.wireframe(true);
	Graphic::ins.cullFaceToogle(false);

	// impl->texture.bind();

	impl->VAO.bind();
	impl->VAO.drawElementTriangle();
	impl->VAO.unbind();

	// Graphic::ins.wireframe(false);
	Graphic::ins.cullFaceToogle(true);
}
