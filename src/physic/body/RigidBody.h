#ifndef __MT_RIGID_BODY_H__
#define __MT_RIGID_BODY_H__

namespace mt {
namespace physic {

class RigidBody
{
public:

	// Variable

	// General
	RigidBody();
	~RigidBody();

	void initPlane(vec3 origin, quat angle, vec3 normal);
	void initSphere(vec3 origin, float radius);
	void close();

	void update();

	void action(bool);

	vec3 getOrigin();

private:

	// Variable
	class RigidBodyImpl;
	RigidBodyImpl* impl;

	friend class Physic;

};

}}

#endif
