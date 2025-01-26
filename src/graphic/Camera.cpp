#define __MT_CAMERA_CPP__

#include "common.h"
#include "engine/Input.h"
#include "engine/Timer.h"
#include "Graphic.h"
#include "Camera.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


Camera::Camera()
{
	this->position = vec3(0,0,3);
	this->forward = vec3(0,0,-1);
	this->right = vec3(1,0,0);
	this->up = vec3(0,1,0);
	this->velocity = vec3();
	this->angle = quat(0,1,0,0);
	this->needUpdate = true;
}

Camera::~Camera()
{
}

void Camera::update()
{
	if (Input::ins.getCursorX() || Input::ins.getCursorY())
	{
		// Delta cursor
		double xoffset = Input::ins.getCursorX();
		double yoffset = Input::ins.getCursorY();

		// Update quaternion
		float angleQ = xoffset * this->sensitivity;
		angle = angle ^ quat(angleQ, vec3(0,1,0));
		angleQ = yoffset * sensitivity;
		quat _tmp = quat(angleQ, vec3(1,0,0)) ^ angle;
		if (_tmp.x * _tmp.x + _tmp.z * _tmp.z < 0.48f)
			angle = _tmp;
		angle = angle.normalize();

		// Update matrix view
		this->forward = vec3(
			2.0f * (angle.x*angle.z - angle.y*angle.w),
			2.0f * (angle.y*angle.z + angle.x*angle.w),
			1.0f - 2.0f * (angle.x*angle.x + angle.y*angle.y)
		);
		
		right = forward ^ vec3(0,1,0);
		right = right.normalize();

		this->needUpdate = true;
	}

	// float speed = 10.0f;
	// float maxSpeed = 20.0f;

	// if (Input::ins.checkHold(87)) // W
	// 	this->velocity = this->movement(this->velocity, this->forward,  speed, maxSpeed, true);
	// if (Input::ins.checkHold(83)) // S
	// 	this->velocity = this->movement(this->velocity, this->forward, -speed, maxSpeed, true);
	// if (Input::ins.checkHold(65)) // A
	// 	this->velocity = this->movement(this->velocity, this->right, -speed, maxSpeed, true);
	// if (Input::ins.checkHold(68)) // D
	// 	this->velocity = this->movement(this->velocity, this->right,  speed, maxSpeed, true);
	
	if (this->velocity.x || this->velocity.y || this->velocity.z)
	{
		// origin = body->getOrigin();

		// g_pView->setPosition(vec3(origin.x, origin.y + 40.0f, origin.z)); // 24 + 40 = 64 / 68

		// vecFront = g_pView->getVeclook();

		// this->right = cross(this->forward, vec3(0,1,0));
		// normalize(this->right);

		// Velocity
		// if (abs(this->velocity.x) < 0.1f && abs(this->velocity.y) < 0.1f && abs(this->velocity.z) < 0.1f)
		// 	this->velocity = vec3();
		// else
		// 	this->velocity *= 0.01f;//0.8f;

		this->position += this->velocity * Timer::ins.getTimePassed();
		this->velocity = vec3(); // Dung ngay lap tuc

		Graphic::ins.shaderProgramMgr.setCameraPosition(position);

		this->needUpdate = true;
	}
	
	if (this->needUpdate)
	{
		Graphic::ins.scene.view.lookAt(position, position + forward, vec3(0,1,0));

		Graphic::ins.shaderProgramMgr.setSceneView(Graphic::ins.scene.view);

		// Update frustum culling
		// this->frustumCulling.update();
	}
}

vec3 Camera::movement(vec3 velocity, vec3 vecdir, float speed, float max_speed, bool yMovement)
{
	vec3 newVelocity = vecdir;

	if (!yMovement)
	{
		newVelocity.y = 0;
		newVelocity = newVelocity.normalize();
	}

	newVelocity *= speed;

	newVelocity.x += velocity.x;
	newVelocity.z += velocity.z;

	if (yMovement)
		newVelocity.y += velocity.y;
	else
		newVelocity.y = velocity.y;

	float lenghtspeed = newVelocity.length();
	if (lenghtspeed > max_speed)
	{
		newVelocity *= (max_speed / lenghtspeed);
	}
	return newVelocity;
}
