#ifndef __FRUSTUMCULLING_H__
#define __FRUSTUMCULLING_H__


class FrustumCulling
{
public:

	// Constructor / Destructor
	FrustumCulling();
	~FrustumCulling();

	// Framework
	void update();

	// Check
	bool isPointInFrustum(vec3 pos);
	bool isSphereInFrustum(vec3 pos, float _radius);
	bool isCubeInFrustum(vec3 pos, float _size);

private:

	// Variable
	float frustum[6][4];
};

#endif
