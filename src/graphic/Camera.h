#ifndef __MT_CAMERA_H__
#define __MT_CAMERA_H__

#include "FrustumCulling.h"

namespace mt {
namespace graphic {

class Camera
{

public:

	// Variable
	vec3 forward, right, up;
	vec3 position, velocity;
	quat angle;
	// vec3 forward, right, up;
	// vec3 position, velocity;
	// quat angle;
	const float sensitivity = 0.002f;
	FrustumCulling frustumCulling;
	bool needUpdate;

	// Forward
	Camera();
	~Camera();
	void update();

	// Native

private:

	// Variables
	double mx, my;

	// Stock
	vec3 movement(vec3 velocity, vec3 vecdir, float speed, float max_speed, bool yMovement);
	// vec3 movement(vec3 velocity, vec3 vecdir, float speed, float max_speed, bool yMovement);

};

}}

#endif
