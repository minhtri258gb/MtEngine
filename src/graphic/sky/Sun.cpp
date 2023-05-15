#define __MT_SUN_CPP__

#include "common.h"
#include "Sun.h"

using namespace mt;
using namespace mt::graphic;

Sun::Sun()
{
	// m_origin = origin;

	// m_origin *= -1;
	// normalize(m_origin);
	// light = new DirectionalLight(m_origin);
}

Sun::~Sun()
{
	// delete light;
}

vec3 Sun::getOrigin()
{
	return origin;
}
