
#include <array>

#include <glm/glm.hpp>

#define DEBUG 1

#define IMPORT_ENGINE
#include "../../Main.h"

#include "../../engine/API/OpenGL/Graphic.h"
extern Graphic *g_pGraphic;

#include "FrustumCulling.h"

#if DEBUG
bool debugFrustumCulling = false;
#endif // DEBUG


FrustumCulling::FrustumCulling()
{
	//ctor
}

FrustumCulling::~FrustumCulling()
{
	//dtor
}

void FrustumCulling::update()
{

#if DEBUG
	if (debugFrustumCulling)
		return;
#endif // DEBUG

	mat4 clip = g_pGraphic->getProjectionMat() * g_pGraphic->getViewMat();

	frustum[0][0] = clip[0][3] - clip[0][0];
	frustum[0][1] = clip[1][3] - clip[1][0];
	frustum[0][2] = clip[2][3] - clip[2][0];
	frustum[0][3] = clip[3][3] - clip[3][0];
	frustum[1][0] = clip[0][3] + clip[0][0];
	frustum[1][1] = clip[1][3] + clip[1][0];
	frustum[1][2] = clip[2][3] + clip[2][0];
	frustum[1][3] = clip[3][3] + clip[3][0];
	frustum[2][0] = clip[0][3] + clip[0][1];
	frustum[2][1] = clip[1][3] + clip[1][1];
	frustum[2][2] = clip[2][3] + clip[2][1];
	frustum[2][3] = clip[3][3] + clip[3][1];
	frustum[3][0] = clip[0][3] - clip[0][1];
	frustum[3][1] = clip[1][3] - clip[1][1];
	frustum[3][2] = clip[2][3] - clip[2][1];
	frustum[3][3] = clip[3][3] - clip[3][1];
	frustum[4][0] = clip[0][3] - clip[0][2];
	frustum[4][1] = clip[1][3] - clip[1][2];
	frustum[4][2] = clip[2][3] - clip[2][2];
	frustum[4][3] = clip[3][3] - clip[3][2];
	frustum[5][0] = clip[0][3] + clip[0][2];
	frustum[5][1] = clip[1][3] + clip[1][2];
	frustum[5][2] = clip[2][3] + clip[2][2];
	frustum[5][3] = clip[3][3] + clip[3][2];

	float t;
	for (int i = 0; i < 6; i++)
	{
		t = (float) sqrt(
				frustum[i][0] * frustum[i][0] + frustum[i][1] * frustum[i][1]
						+ frustum[i][2] * frustum[i][2]);
		frustum[i][0] /= t;
		frustum[i][1] /= t;
		frustum[i][2] /= t;
		frustum[i][3] /= t;
	}
}

bool FrustumCulling::isPointInFrustum(vec3 pos)
{
	for (int i = 0; i < 6; i++)
		if (frustum[i][0] * pos.x + frustum[i][1] * pos.y
				+ frustum[i][2] * pos.z + frustum[i][3] <= 0)
			return false;
	return true;
}

bool FrustumCulling::isSphereInFrustum(vec3 pos, float _radius)
{
	for (int i = 0; i < 6; i++)
		if (frustum[i][0] * pos.x + frustum[i][1] * pos.y
				+ frustum[i][2] * pos.z + frustum[i][3] <= -_radius)
			return false;
	return true;
}

bool FrustumCulling::isCubeInFrustum(vec3 pos, float _size)
{
	for (int i = 0; i < 6; i++)
	{
		if (frustum[i][0] * (pos.x - _size) + frustum[i][1] * (pos.y - _size)
				+ frustum[i][2] * (pos.z - _size) + frustum[i][3] > 0)
			continue;
		if (frustum[i][0] * (pos.x + _size) + frustum[i][1] * (pos.y - _size)
				+ frustum[i][2] * (pos.z - _size) + frustum[i][3] > 0)
			continue;
		if (frustum[i][0] * (pos.x - _size) + frustum[i][1] * (pos.y + _size)
				+ frustum[i][2] * (pos.z - _size) + frustum[i][3] > 0)
			continue;
		if (frustum[i][0] * (pos.x + _size) + frustum[i][1] * (pos.y + _size)
				+ frustum[i][2] * (pos.z - _size) + frustum[i][3] > 0)
			continue;
		if (frustum[i][0] * (pos.x - _size) + frustum[i][1] * (pos.y - _size)
				+ frustum[i][2] * (pos.z + _size) + frustum[i][3] > 0)
			continue;
		if (frustum[i][0] * (pos.x + _size) + frustum[i][1] * (pos.y - _size)
				+ frustum[i][2] * (pos.z + _size) + frustum[i][3] > 0)
			continue;
		if (frustum[i][0] * (pos.x - _size) + frustum[i][1] * (pos.y + _size)
				+ frustum[i][2] * (pos.z + _size) + frustum[i][3] > 0)
			continue;
		if (frustum[i][0] * (pos.x + _size) + frustum[i][1] * (pos.y + _size)
				+ frustum[i][2] * (pos.z + _size) + frustum[i][3] > 0)
			continue;
		return false;
	}
	return true;
}

void cmd_debugfrustumculling()
{
	debugFrustumCulling = !debugFrustumCulling;
}
