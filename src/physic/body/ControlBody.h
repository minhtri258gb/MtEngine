#ifndef __MT_CONTROL_BODY_H__
#define __MT_CONTROL_BODY_H__

namespace mt {
namespace physic {

class ControlBody
{
public:

	// Variable

	// General
	ControlBody();
	~ControlBody();

	void createCapsule(vec3 origin);
	void close();

	void update();

	void action(bool);

	void getTransForm(vec3 *origin, quat *angle);

	vec3 getOrigin();
	void setOrigin(vec3 pos);
	void setGravity(float gravity);
	
	void setWalkDirection(vec3 velocity);
	void setLinearVelocity(vec3 velocity);
	void jump(float force);
	
	bool onGround();

private:

	// Variable
	class ControlBodyImpl;
	ControlBodyImpl* impl;

	friend class Physic;

};

}}

#endif
