#define __MT_TEST_QUATERNION_CPP__

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

#include <LinearMath/btQuaternion.h>
#include <LinearMath/btMatrix3x3.h>

#include "common.h"
#include "TestQuaternion.h"

using namespace std;
using namespace mt;
using namespace mt::test;

void TestQuaternion::run()
{

	// [X] Constructor with x, y, z, w
	float x=1.5, y=1.1, z=1.2, w=1;
	quat mtQuat(x, y, z, w); // Quaternion(float x, float y, float z, float w)
	glm::quat glQuat = glm::quat(w, x, y, z); // qua(T _w, T _x, T _y, T _z)
	btQuaternion btQuat(x, y, z, w); // btQuaternion(const btScalar& _x, const btScalar& _y, const btScalar& _z, const btScalar& _w)
	
	float x2=1.8, y2=2.1, z2=2.4, w2=1;
	quat mtQuat2(x2, y2, z2, w2); // Quaternion(float x, float y, float z, float w)
	glm::quat glQuat2 = glm::quat(w2, x2, y2, z2); // qua(T _w, T _x, T _y, T _z)
	btQuaternion btQuat2(x2, y2, z2, w2); // btQuaternion(const btScalar& _x, const btScalar& _y, const btScalar& _z, const btScalar& _w)

	// [X] Constructor with Angle Axis
	// float angle=PI/2.0f, x=20, y=10, z=30;
	// quat mtQuat(angle, vec3(x,y,z)); // float angle, Vector3 axis
	// btQuaternion btQuat(btVector3(x,y,z), angle); // btQuaternion(const btVector3& _axis, const btScalar& _angle)

	// [ ] (glm ERR) Constructor with pitch, yaw, roll
	// float pitch=1, yaw=1.2, roll=1.4;
	// quat mtQuat(pitch, yaw, roll); // pitch, yaw, roll
	// glm::quat glQuat = glm::quat(glm::vec3(pitch, yaw, roll)); // ?
	// btQuaternion btQuat(yaw, pitch, roll); // btQuaternion(const btScalar& yaw, const btScalar& pitch, const btScalar& roll)
	
	// [X] (bt Unkown) conjugate
	// mtQuat = mtQuat.conjugate();
	// glQuat = glm::conjugate(glQuat);
	// btQuat = ?

	// [ ] (mt Unkown, bt is conjugate) inverse
	// mtQuat = mtQuat. ?
	// glQuat = glm::inverse(glQuat);
	// btQuat = btQuat.inverse(); // conjugate ?

	// [X] length
	// cout << "mtQuat: " << mtQuat.length() << endl;
	// cout << "glQuat: " << glm::length(glQuat) << endl;
	// cout << "btQuat: " << btQuat.length() << endl;

	// [X] length2
	// cout << "mtQuat: " << mtQuat.length2() << endl;
	// cout << "glQuat: " << glm::length2(glQuat) << endl;
	// cout << "btQuat: " << btQuat.length2() << endl;

	// [X] (bt none) lerp
	// mtQuat = mtQuat.lerp(mtQuat2, 0.5f);
	// glQuat = glm::lerp(glQuat, glQuat2, 0.5f);
	// btQuat = btQuat.lerp(btQuat, btQuat2);

	// [X] (bt high accu) slerp
	// mtQuat = mtQuat.slerp(mtQuat2, 0.5f);
	// glQuat = glm::slerp(glQuat, glQuat2, 0.5f);
	// btQuat = btQuat.slerp(btQuat2, 0.5f);

	// [X] dot product
	// cout << "mtQuat: " << mtQuat * mtQuat2 << endl;
	// cout << "glQuat: " << glm::dot(glQuat, glQuat2) << endl;
	// cout << "btQuat: " << btQuat.dot(btQuat2) << endl;
	
	// [X] (bt Unkown) Cross product
	// mtQuat = mtQuat ^ mtQuat2;
	// glQuat = glm::cross(glQuat, glQuat2);
	// btQuat = btQuat.cross

	// [ ] (mt|gl Unkown) Angle between 2 quaternion
	// cout << "mtQuat: " << mtQuat.angle(mtQuat2) << endl;
	// cout << "glQuat: " << glm::angle(glQuat, glQuat2) << endl;
	// cout << "btQuat: " << btQuat.angle(btQuat2) << endl;

	// [ ] (bt other result) To Matrix 3x3
	// mat3 mtMat3 = mat3(mtQuat);
	// glm::mat3 glMat3 = glm::mat3_cast(glQuat);
	// btMatrix3x3 btMat3 = btMatrix3x3(btQuat);

	// [ ] (bt none) To Matrix 4x4
	// mat4 mtMat4 = mat4(mtQuat);
	// glm::mat4 glMat4 = glm::mat4_cast(glQuat);
	// btMatrix4x4 btMat4 = btMatrix4x4(btQuat);

	// [X] Operator +
	// mtQuat = mtQuat + mtQuat2;
	// glQuat = glQuat + glQuat2;
	// btQuat = btQuat + btQuat2;

	// [X] Operator -
	mtQuat = mtQuat - mtQuat2;
	glQuat = glQuat - glQuat2;
	btQuat = btQuat - btQuat2;

	// Compare
	cout << "mtQuat: [" << mtQuat.x << "] [" << mtQuat.y << "] [" << mtQuat.z << "] [" << mtQuat.w << "]\n";
	cout << "glQuat: [" << glQuat.x << "] [" << glQuat.y << "] [" << glQuat.z << "] [" << glQuat.w << "]\n";
	cout << "btQuat: [" << btQuat.getX() << "] [" << btQuat.getY() << "] [" << btQuat.getZ() << "] [" << btQuat.getW() << "]\n";

	// cout << "mtMat3: " << endl;
	// cout << "\t" << mtMat3[0] << " " << mtMat3[1] << " " << mtMat3[2] << endl;
	// cout << "\t" << mtMat3[3] << " " << mtMat3[4] << " " << mtMat3[5] << endl;
	// cout << "\t" << mtMat3[6] << " " << mtMat3[7] << " " << mtMat3[8] << endl;
	// cout << "glMat3: " << endl;
	// cout << "\t" << glMat3[0][0] << " " << glMat3[0][1] << " " << glMat3[0][2] << endl;
	// cout << "\t" << glMat3[1][0] << " " << glMat3[1][1] << " " << glMat3[1][2] << endl;
	// cout << "\t" << glMat3[2][0] << " " << glMat3[2][1] << " " << glMat3[2][2] << endl;
	// cout << "btMat3: " << endl;
	// cout << "\t" << btMat3[0][0] << " " << btMat3[0][1] << " " << btMat3[0][2] << endl;
	// cout << "\t" << btMat3[1][0] << " " << btMat3[1][1] << " " << btMat3[1][2] << endl;
	// cout << "\t" << btMat3[2][0] << " " << btMat3[2][1] << " " << btMat3[2][2] << endl;

	// cout << "mtMat4: " << endl;
	// cout << "\t" << mtMat4[ 0] << " " << mtMat4[ 1] << " " << mtMat4[ 2] << " " << mtMat4[ 3] << endl;
	// cout << "\t" << mtMat4[ 4] << " " << mtMat4[ 5] << " " << mtMat4[ 6] << " " << mtMat4[ 7] << endl;
	// cout << "\t" << mtMat4[ 8] << " " << mtMat4[ 9] << " " << mtMat4[10] << " " << mtMat4[11] << endl;
	// cout << "\t" << mtMat4[12] << " " << mtMat4[13] << " " << mtMat4[14] << " " << mtMat4[15] << endl;
	// cout << "glMat4: " << endl;
	// cout << "\t" << glMat4[0][0] << " " << glMat4[0][1] << " " << glMat4[0][2] << " " << glMat4[0][3] << endl;
	// cout << "\t" << glMat4[1][0] << " " << glMat4[1][1] << " " << glMat4[1][2] << " " << glMat4[1][3] << endl;
	// cout << "\t" << glMat4[2][0] << " " << glMat4[2][1] << " " << glMat4[2][2] << " " << glMat4[2][3] << endl;
	// cout << "\t" << glMat4[3][0] << " " << glMat4[3][1] << " " << glMat4[3][2] << " " << glMat4[3][3] << endl;


	// GLM
	// detail::tquat< T > 	mix (detail::tquat< T > const &x, detail::tquat< T > const &y, typename detail::tquat< T >::value_type const &a)
	//  	Returns a SLERP interpolated quaternion of x and y according a.
	// detail::tquat< T > 	normalize (detail::tquat< T > const &q)
	//  	Returns the normalized quaternion of from x.
	// detail::tquat< T > 	quat_cast (detail::tmat4x4< T > const &x)
	//  	Converts a 4 * 4 matrix to a quaternion.
	// detail::tquat< T > 	quat_cast (detail::tmat3x3< T > const &x)
	//  	Converts a 3 * 3 matrix to a quaternion.
	// detail::tquat< T > 	rotate (detail::tquat< T > const &q, typename detail::tquat< T >::value_type const &angle, detail::tvec3< T > const &v)
	//  	Rotates a quaternion from an vector of 3 components axis and an angle expressed in degrees.


	// Bullet
	// void 	getEulerZYX (btScalar &yawZ, btScalar &pitchY, btScalar &rollX) const
	// btQuaternion & 	operator+= (const btQuaternion &q)
	// btQuaternion & 	operator-= (const btQuaternion &q)
	// btQuaternion & 	operator*= (const btScalar &s)
	// btQuaternion & 	operator*= (const btQuaternion &q)
	// btQuaternion & 	safeNormalize ()
	// btQuaternion & 	normalize ()
	// btQuaternion 	operator* (const btScalar &s) const
	// btQuaternion 	operator/ (const btScalar &s) const
	// btQuaternion & 	operator/= (const btScalar &s)
	// btQuaternion 	normalized () const
	// btScalar 	angleShortestPath (const btQuaternion &q) const
	// btScalar 	getAngle () const
	// btScalar 	getAngleShortestPath () const
	// btVector3 	getAxis () const
	// btQuaternion 	operator+ (const btQuaternion &q2) const
	// btQuaternion 	operator- (const btQuaternion &q2) const
	// btQuaternion 	operator- () const
	// btQuaternion 	farthest (const btQuaternion &qd) const
	// btQuaternion 	nearest (const btQuaternion &qd) const
}
