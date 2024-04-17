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

	void create(std::string name, vec3 pos, quat rot, vec3 scale);
	void update();
	void close();

	void action(bool);

	void getTransForm(vec3 *origin, quat *angle);
	vec3 getOrigin();

private:

	// Variable
	class RigidBodyImpl;
	RigidBodyImpl* impl;

	friend class Physic;

};

}}

#endif
