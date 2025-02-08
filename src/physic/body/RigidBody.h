#ifndef __MT_RIGID_BODY_H__
#define __MT_RIGID_BODY_H__

namespace mt {
namespace physic {

class RigidBody {
public:

	// Variable

	// General
	RigidBody();
	~RigidBody();

	void update();
	void clear();

	void action(bool);
	void getTransForm(vec3 *origin, quat *angle);
	vec3 getOrigin();
	void force(vec3);
	void setVelocity(vec3);

private:

	// Variable
	class RigidBodyImpl;
	RigidBodyImpl* impl;

	friend class PhysicBuilder;

};

}}

#endif
