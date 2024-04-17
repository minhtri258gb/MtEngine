#define __MT_PLAYER_CPP__

#include "common.h"
#include "engine/Timer.h"
#include "graphic/Graphic.h"
#include "physic/body/ControlBody.h"
#include "Player.h"

//#define SPEED_WALK 50.0f
//#define SPEED_RUN 5200.0f
//#define MAXSPEEDMOVE 8000.0f
//#define RANGE_USE 64.0f

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;
using namespace mt::physic;
using namespace mt::game;


// const float Player::h_eyeHight = 40.0f;
// ControlBody* Player::m_body;
// vec3 Player::m_origin;
// vec3 Player::m_vecFront, Player::m_vecRight;
// vec3 Player::m_velocity;
// float Player::m_angle;
// bool Player::m_sprint;
// bool Player::m_noclip;

class Player::PlayerImpl
{
public:
	
	// Variable
	ControlBody* body;

	// Method

};

Player::Player()
{
	// Implement
	impl = new PlayerImpl();

	// m_origin = vec3();

	// m_vecFront = vec3(0.0f, 1.0f, 0.0f);
	// m_vecRight = vec3(1.0f, 0.0f, 0.0f);
	// m_velocity = vec3();
	// m_angle = 0.0f;
	// m_sprint = false;
	// m_noclip = true;

	// if (m_noclip)
	// 	impl->body->setGravity(0.0f);
}

Player::~Player()
{
	if (impl->body)
	{
		impl->body->close();
		delete impl->body;
		impl->body = nullptr;
	}

	// Implement
	delete impl;
}

void Player::init()
{
	// Body
	impl->body = new ControlBody();
	// impl->body->createCapsule(m_origin);
	impl->body->createCapsule(vec3());
	impl->body->action(true);

}

void Player::update()
{
	vec3 origin = impl->body->getOrigin();
	this->origin = origin;

	Graphic::ins.camera.position = vec3(origin.x, origin.y, origin.z + 0.0f); // h_eyeHight
	Graphic::ins.camera.needUpdate = true;

	vec3 vecFront = Graphic::ins.camera.forward;
	vec3 vecRight = Graphic::ins.camera.right;

	// Velocity
	vec3 velocity = this->velocity;
	if (abs(velocity.x) < 0.1f && abs(velocity.y) < 0.1f && abs(velocity.z) < 0.1f)
		velocity = vec3();
	else
		velocity *= 0.8f;
	this->velocity = velocity;

	// velocity = vec3(); // DEBUG
	impl->body->setWalkDirection(velocity * Timer::ins.getTimePassed());
}

void Player::movement(int direct)
{
	vec3 vecdir;
	if (1 == direct) // 
		vecdir = Graphic::ins.camera.forward;
	else if (2 == direct) // 
		vecdir = -Graphic::ins.camera.forward;
	else if (3 == direct) // 
		vecdir = -Graphic::ins.camera.right;
	else if (4 == direct) // 
		vecdir = Graphic::ins.camera.right;
	

	float speed = 100.0f;
	// if (m_sprint)
	// 	speed = 1000.0f;

	float max_speed = 4000.0f;

	vec3 newVelocity = vecdir;

	// if (!m_noclip)
	// 	newVelocity.z = 0;

	newVelocity = newVelocity.normalize();
	newVelocity *= speed;

	this->velocity += newVelocity;

	float lenghtspeed = this->velocity.length();
	if (lenghtspeed > max_speed)
		this->velocity *= (max_speed / lenghtspeed);
}

//void Player::use()
//{
////	void* pUser = NULL;
////
////	Vec3 end = origin + vecFront * RANGE_USE;
////	if(engine.world->raycast(origin, end, pUser)) {
////		MyEntity* pMyEntity = NULL;
////		if(pUser != NULL) {
////			pMyEntity = (MyEntity*)pUser;
////			pMyEntity->model->force(Vec3(0, 1000, 0));
////		}
////	}
//}

// void Player::cmd_noclip()
// {
// 	// if(m_noclip)
// 	// 	m_body->setGravity(1024.0f);
// 	// else
// 	// 	m_body->setGravity(0.0f);

// 	// m_noclip = !m_noclip;
// }

// vec3 Player::getOrigin()
// {
// 	return m_origin;
// }

// void Player::setOrigin(vec3 origin)
// {
// 	m_body->setOrigin(origin);
// }

//bool Player::onGround()
//{
//	return body->onGround();
//}

// void Player::cmd_jump()
// {
// 	if (!m_noclip)
// 		m_body->jump(512.0f);
// }

// void Player::cmd_sprint()
// {
// 	m_sprint = !m_sprint;
// }

// void Player::cmd_origin()
// {
// 	cout << m_origin.x << " " << m_origin.y <<" " << m_origin.z << endl;
// }
