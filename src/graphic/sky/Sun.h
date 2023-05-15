#ifndef __MT_SUN_H__
#define __MT_SUN_H__

// #include "../light/DirectionalLight.h"

namespace mt {
namespace graphic {

class Sun
{
public:

	// Variables
	// DirectionalLight *light;

	// Forwards
	Sun();
	~Sun();

	// Natives
	vec3 getOrigin();

	// Other
	friend class SkyBox;

private:

	// Variable
	vec3 origin;

};

}}

#endif
