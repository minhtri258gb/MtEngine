#ifndef __MT_FRUSTUM_CULLING_H__
#define __MT_FRUSTUM_CULLING_H__

namespace mt {
namespace graphic {

class FrustumCulling
{
public:

	// Forwards
	FrustumCulling();
	~FrustumCulling();
	void update();

	// Natives
	bool point(vec3 pos);
	bool point2(vec3 pos);
	bool sphere(vec3 pos, float radius);
	int spherePart(vec3 pos, float radius);
	float sphereDis(vec3 pos, float radius);
	bool cube(vec3 pos, float size);
	bool cube2(vec3 v[8]);
	int cubePart(vec3 pos, float size);
	bool polygon(std::vector<vec3> points);

	void debug();

private:

	// Variable
	vec4 frustum[6]; // UDRLFB

};

}}

#endif
