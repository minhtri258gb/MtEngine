#define __MT_VECTOR_3_CPP__

#include <sstream>
#include <cmath>

#include "Math3D.h"
#include "../../exception/Exception.h"

using namespace std;
using namespace mt;

Vector3::Vector3()
{
	this->set(0.0f, 0.0f, 0.0f);
}

Vector3::Vector3(float x, float y, float z)
{
	this->set(x, y, z);
}

Vector3::Vector3(const Vector3 &v)
{
	this->set(v);
}

Vector3::~Vector3()
{
}

float Vector3::squareLength() const
{
	return x*x + y*y + z*z;
}

float Vector3::length() const
{
	return sqrtf(x*x + y*y + z*z);
}

Vector3 Vector3::normalize()
{
    return *this / length();
}

Vector3 Vector3::rotate(const Quaternion& _q)
{
	Quaternion q2(x, y, z, 0.0f), q = _q, qinv = q.conjugate();
	q = q ^ q2 ^ qinv;
	return Vector3(q.x,q.y,q.z);
}

void Vector3::set(float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

void Vector3::set(const Vector3 &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

bool Vector3::equal(const Vector3& v, double epsilon) const
{
    return
        abs(x - v.x) <= epsilon &&
        abs(y - v.y) <= epsilon &&
        abs(z - v.z) <= epsilon;
}

Vector3 Vector3::mix(const Vector3& v, float factor)
{
	return *this * (1.0f - factor) + v * factor;
}

Vector3 Vector3::operator + (const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator - (const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator * (float f) const
{
	return Vector3(x*f, y*f, z*f);
}

Vector3 Vector3::operator / (float f) const
{
	return Vector3(x/f, y/f, z/f);
}

float Vector3::operator * (const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::operator ^ (const Vector3& v) const
{
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

const Vector3& Vector3::operator += (const Vector3& v)
{
    x += v.x;
	y += v.y;
	z += v.z;
    return *this;
}

const Vector3& Vector3::operator -= (const Vector3& v)
{
    x -= v.x;
	y -= v.y;
	z -= v.z;
    return *this;
}

const Vector3& Vector3::operator *= (float f)
{
    x *= f;
	y *= f;
	z *= f;
    return *this;
}

const Vector3& Vector3::operator /= (float f)
{
    x /= f;
	y /= f;
	z /= f;
    return *this;
}

bool Vector3::operator == (const Vector3& v) const
{
	return x == v.x && y == v.y && z == v.z;
}

bool Vector3::operator != (const Vector3& v) const
{
	return x != v.x || y != v.y || z != v.z;
}

float Vector3::operator [] (unsigned int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
    }
}

float& Vector3::operator [] (unsigned int index)
{
	if (index < 0 || index > 2)
	{
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
	}
	return *(&x + index);
}

Vector3& Vector3::operator = (const Vector3 &v)
{
	this->set(v);
    return *this;
}

Vector3 Vector3::operator - ()
{
	return Vector3(-x, -y, -z);
}
