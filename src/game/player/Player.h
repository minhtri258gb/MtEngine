#ifndef __MT_PLAYER_H__
#define __MT_PLAYER_H__


namespace mt {
namespace game {

class Player {
public:

	// Variable
	vec3 origin;
	vec3 velocity;

	// Forwards
	Player();
	~Player();

	void init();
	void update();

	void movement(int direct);

	// General
//	void camMove(int direct);

	// Event
	// static void cmd_jump();
	// static void cmd_sprint();
	// static void cmd_origin();
//	void cmd_use();
	// static void cmd_noclip();

	// Get / Set
	// static vec3 getOrigin();
	// static void setOrigin(vec3);
//	void setSprint(bool);

	// Check
//	bool onGround();

private:

	// Variable
	// static const float h_eyeHight;
	// static vec3 m_origin;
	// static vec3 m_vecFront, m_vecRight;
	// static vec3 m_velocity;
	// static float m_angle;
	// static bool m_sprint;
	// static bool m_noclip;

	// Math

private:

	// Variables
	class PlayerImpl;
	PlayerImpl* impl;

};

}}

#endif
