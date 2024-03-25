#define __MT_TERRAIN_QUAD_CPP__

#include "common.h"
#include "engine/Input.h"
#include "../Graphic.h"
#include "TerrainQuad.h"

#include "engine/datatype/Flag32.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;

TerrainQuad::TerrainQuad()
{
	parent = nullptr;

	for (unsigned char i=0; i<4; i++)
		children[i] = neighbor[i] = nullptr;

	level = 0;
	position = vec2();
}

TerrainQuad::~TerrainQuad()
{
	for (unsigned char i=0; i<4; i++)
		if (children[i])
			delete children[i];
}

/**
 * Index of children:
 *   0  2
 *   1  3
 **/
void TerrainQuad::generateTreeEx(unsigned char level, TerrainQuad* parent, vec2 _position)
{
	this->level = level;
	this->parent = parent;
	this->position = _position;

	if (level > 1)
	{
		int halfSize = (1 << level - 1);
		float minX = _position.x;
		float minZ = _position.y;
		float midX = minX + halfSize;
		float midZ = minZ + halfSize;

		children[0] = new TerrainQuad();
		children[0]->generateTreeEx(level - 1, this, vec2(minX, minZ));
		
		children[1] = new TerrainQuad();
		children[1]->generateTreeEx(level - 1, this, vec2(minX, midZ));
		
		children[2] = new TerrainQuad();
		children[2]->generateTreeEx(level - 1, this, vec2(midX, minZ));
		
		children[3] = new TerrainQuad();
		children[3]->generateTreeEx(level - 1, this, vec2(midX, midZ));
	}
}

/**
 * Index of neighbor: same tess control
 *			0
 * 		1		3
 * 			2
 **/
void TerrainQuad::generateNeighborEx(TerrainQuad* n0, TerrainQuad* n1, TerrainQuad* n2, TerrainQuad* n3)
{
    neighbor[0] = n0;
    neighbor[1] = n1;
    neighbor[2] = n2;
    neighbor[3] = n3;

    TerrainQuad *noc1, *noc2; // Neighbor outter of children

	if(children[0])
	{
		noc1 = n0 ? n0->children[1] : nullptr;
		noc2 = n1 ? n1->children[2] : nullptr;
		children[0]->generateNeighborEx(noc1, noc2, children[1], children[2]);
	}

	if(children[1])
	{
		noc1 = n1 ? n1->children[3] : nullptr;
		noc2 = n2 ? n2->children[0] : nullptr;
		children[1]->generateNeighborEx(children[0], noc1, noc2, children[3]);
	}

	if(children[2])
	{
		noc1 = n0 ? n0->children[3] : nullptr;
		noc2 = n3 ? n3->children[0] : nullptr;
		children[2]->generateNeighborEx(noc1, children[0], children[3], noc2);
	}

	if(children[3])
	{
		noc1 = n2 ? n2->children[2] : nullptr;
		noc2 = n3 ? n3->children[1] : nullptr;
		children[3]->generateNeighborEx(children[2], children[1], noc1, noc2);
	}
}

void TerrainQuad::update()
{
	// Frustum cull
	int halfsize = 1 << (level - 1);
	float midX = position.x + halfsize;
	float midZ = position.y + halfsize;

	vec3 center(midX, 0.0f, midZ);
	
	// isVisible = Graphic::ins.camera.frustumCulling.sphere(center, halfsize * 2.0f + 128.0); // #TODO
	// isVisible = Graphic::ins.camera.frustumCulling.point(center); // #DEBUG
	isVisible = true; // #TODO remove
	if (!isVisible)
	{
		isRender = true;
		return;
	}

	// Level of Detail
	vec3 eyePos = Graphic::ins.camera.position;
	vec3 vecdis = eyePos - center;
	float distance = vecdis.length();

	if(distance > (1 << (level+1)) || level == 1)
		isRender = true;
	else
	{
		isRender = false;
		for(short i=0; i<4; i++)
			if(children[i])
				children[i]->update();
	}
}

void TerrainQuad::getData(unsigned int& count, std::vector<vec2>& positions, vector<int>& levels, vector<int>& flags)
{
	if (!isVisible)
		return;

	if (isRender)
	{
		// Check patch
		Flag32 patch;
		for (int i=0; i<4; i++)
			if (neighbor[i] && neighbor[i]->parent->isRender)
				patch.setOn(i);
		
		// Set data
		count++;
		positions.push_back(position);
		levels.push_back(level);
		flags.push_back(patch.get());
	}
	else
	{
		for (unsigned char i=0; i<4; i++)
			if(children[i])
				children[i]->getData(count, positions, levels, flags);
	}
}
