#define __MT_FRUSTUM_CULLING_CPP__

#include <cmath>

#include "common.h"
#include "engine/Config.h"
#include "engine/Input.h"
#include "Graphic.h"
#include "FrustumCulling.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;

bool debug_frustumCulling = false;

FrustumCulling::FrustumCulling()
{
}

FrustumCulling::~FrustumCulling()
{
}

void FrustumCulling::update()
{
	if (debug_frustumCulling)
		return;
	
	// mat4 m = Graphic::ins.scene.proj * Graphic::ins.scene.view;
	// frustum[0] = vec4(m[ 3] + m[ 0], m[ 7] + m[ 4], m[11] + m[ 8], m[15] + m[12]).normalize(); // left
	// frustum[1] = vec4(m[ 3] - m[ 0], m[ 7] - m[ 4], m[11] - m[ 8], m[15] - m[12]).normalize(); // right
	// frustum[2] = vec4(m[ 3] - m[ 1], m[ 7] - m[ 5], m[11] - m[ 9], m[15] - m[13]).normalize(); // top
	// frustum[3] = vec4(m[ 3] + m[ 1], m[ 7] + m[ 5], m[11] + m[ 9], m[15] + m[13]).normalize(); // bottom

	mat4 m = Graphic::ins.scene.proj * Graphic::ins.scene.view;
	frustum[0] = vec4(m[3] + m[2], m[7] + m[6], m[11] + m[10], m[15] + m[14]).normalize(); // near
	frustum[1] = vec4(m[3] - m[2], m[7] - m[6], m[11] - m[10], m[15] - m[14]).normalize(); // far
	frustum[2] = vec4(m[3] + m[0], m[7] + m[4], m[11] + m[ 8], m[15] + m[12]).normalize(); // left
	frustum[3] = vec4(m[3] - m[0], m[7] - m[4], m[11] - m[ 8], m[15] - m[12]).normalize(); // right
	frustum[4] = vec4(m[3] - m[1], m[7] - m[5], m[11] - m[ 9], m[15] - m[13]).normalize(); // top
	frustum[5] = vec4(m[3] + m[1], m[7] + m[5], m[11] + m[ 9], m[15] + m[13]).normalize(); // bottom

}

bool FrustumCulling::point(vec3 pos)
{
	for (int i=0; i<6; i++) 
		if (frustum[i] * vec4(pos.x, pos.y, pos.z, 1.0f) <= 0)
			return false;
	return true;
}

bool FrustumCulling::sphere(vec3 pos, float radius)
{
	for (int i=0; i<4; i++)
		if (frustum[i] * vec4(pos.x, pos.y, pos.z, 1.0f) <= -radius)
			return false;
	return true;
}

int FrustumCulling::spherePart(vec3 pos, float radius)
{
	int c = 0;
	float d;
	for (int i=0; i<4; i++)
	{
		d = frustum[i] * vec4(pos.x, pos.y, pos.z, 1.0f);
		if (d <= -radius)
			return 0;
		if (d > radius)
			c++;
	}
	return (c == 4) ? 2 : 1;
}

float FrustumCulling::sphereDis(vec3 pos, float radius)
{
	float d;
	for (int i=0; i<4; i++)
	{
		d = frustum[i] * vec4(pos.x, pos.y, pos.z, 1.0f);
		if (d <= -radius)
			return 0;
	}
	return d + radius;
}

bool FrustumCulling::cube(vec3 pos, float size)
{
	for (int i=0; i<4; i++)
	{
		if (frustum[i].x * (pos.x - size) + frustum[i].y * (pos.y - size) + frustum[i].z * (pos.z - size) + frustum[i].w > 0)
			continue;
		if (frustum[i].x * (pos.x + size) + frustum[i].y * (pos.y - size) + frustum[i].z * (pos.z - size) + frustum[i].w > 0)
			continue;
		if (frustum[i].x * (pos.x - size) + frustum[i].y * (pos.y + size) + frustum[i].z * (pos.z - size) + frustum[i].w > 0)
			continue;
		if (frustum[i].x * (pos.x + size) + frustum[i].y * (pos.y + size) + frustum[i].z * (pos.z - size) + frustum[i].w > 0)
			continue;
		if (frustum[i].x * (pos.x - size) + frustum[i].y * (pos.y - size) + frustum[i].z * (pos.z + size) + frustum[i].w > 0)
			continue;
		if (frustum[i].x * (pos.x + size) + frustum[i].y * (pos.y - size) + frustum[i].z * (pos.z + size) + frustum[i].w > 0)
			continue;
		if (frustum[i].x * (pos.x - size) + frustum[i].y * (pos.y + size) + frustum[i].z * (pos.z + size) + frustum[i].w > 0)
			continue;
		if (frustum[i].x * (pos.x + size) + frustum[i].y * (pos.y + size) + frustum[i].z * (pos.z + size) + frustum[i].w > 0)
			continue;
		return false;
	}
	return true;
}

int FrustumCulling::cubePart(vec3 pos, float size)
{
	int c;
	int c2 = 0;
	for (int i=0; i<4; i++)
	{
		c = 0;
		if (frustum[i].x * (pos.x - size) + frustum[i].y * (pos.y - size) + frustum[i].z * (pos.z - size) + frustum[i].w > 0)
			c++;
		if (frustum[i].x * (pos.x + size) + frustum[i].y * (pos.y - size) + frustum[i].z * (pos.z - size) + frustum[i].w > 0)
			c++;
		if (frustum[i].x * (pos.x - size) + frustum[i].y * (pos.y + size) + frustum[i].z * (pos.z - size) + frustum[i].w > 0)
			c++;
		if (frustum[i].x * (pos.x + size) + frustum[i].y * (pos.y + size) + frustum[i].z * (pos.z - size) + frustum[i].w > 0)
			c++;
		if (frustum[i].x * (pos.x - size) + frustum[i].y * (pos.y - size) + frustum[i].z * (pos.z + size) + frustum[i].w > 0)
			c++;
		if (frustum[i].x * (pos.x + size) + frustum[i].y * (pos.y - size) + frustum[i].z * (pos.z + size) + frustum[i].w > 0)
			c++;
		if (frustum[i].x * (pos.x - size) + frustum[i].y * (pos.y + size) + frustum[i].z * (pos.z + size) + frustum[i].w > 0)
			c++;
		if (frustum[i].x * (pos.x + size) + frustum[i].y * (pos.y + size) + frustum[i].z * (pos.z + size) + frustum[i].w > 0)
			c++;
		if (c == 0)
			return 0;
		if (c == 8)
			c2++;
	}
	return (c2 == 4) ? 2 : 1;
}

bool FrustumCulling::polygon(std::vector<vec3> points)
{
	for (int i=0; i<4; i++)
	{
		int j;
		int size = points.size();
		for (j=0; j<size; j++)
		{
			vec3 p = points[j];
			if (frustum[i] * vec4(p.x, p.y, p.z, 1.0f) > 0)
				break;
		}
		if (j == size)
			return false;
	}
	return true;
}

void FrustumCulling::debug()
{
	debug_frustumCulling = !debug_frustumCulling;
}
