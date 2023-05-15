#define __MT_VECTOR_4_CPP__

#include <sstream>
#include <cmath>

#include "Vector4.h"
#include "../../exception/Exception.h"

using namespace std;
using namespace mt;

Vector4::Vector4()
{
	this->set(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->set(x, y, z, w);
}

Vector4::Vector4(const Vector4& v)
{
	this->set(v);
}

Vector4::~Vector4()
{
}

float Vector4::squareLength() const
{
	return x*x + y*y + z*z + w*w;
}

float Vector4::length() const
{
	return sqrtf(x*x + y*y + z*z + w*w);
}

Vector4 Vector4::normalize()
{
	return *this / length();
}

void Vector4::set(float _x, float _y, float _z, float _w)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
}

void Vector4::set(const Vector4 &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}

bool Vector4::equal(const Vector4& v, double epsilon) const
{
    return
        abs(x - v.x) <= epsilon &&
        abs(y - v.y) <= epsilon &&
        abs(z - v.z) <= epsilon &&
        abs(w - v.w) <= epsilon;
}

Vector4 Vector4::operator + (const Vector4& v) const
{
    return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator - (const Vector4& v) const
{
    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4 Vector4::operator * (float f) const
{
    return Vector4(x*f, y*f, z*f, w*f);
}

float Vector4::operator * (const Vector4& v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.x;
}

Vector4 Vector4::operator / (float f) const
{
    return Vector4(x/f, y/f, z/f, w/f);
}

const Vector4& Vector4::operator += (const Vector4& v)
{
    x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
    return *this;
}

const Vector4& Vector4::operator -= (const Vector4& v)
{
    x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
    return *this;
}

const Vector4& Vector4::operator *= (float f)
{
    x *= f;
	y *= f;
	z *= f;
	w *= f;
    return *this;
}

const Vector4& Vector4::operator /= (float f)
{
    x /= f;
	y /= f;
	z /= f;
	w /= f;
    return *this;
}

bool Vector4::operator == (const Vector4& v) const
{
	return  x == v.x && y == v.y && z == v.z && w == v.w;
}

bool Vector4::operator != (const Vector4& v) const
{
	return x != v.x || y != v.y || z != v.z || w != v.w;
}

float Vector4::operator [] (unsigned int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
    }
}

float& Vector4::operator [] (unsigned int index)
{
	if (index < 0 || index > 3)
	{
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
	}
	return *(&x + index);
}

Vector4& Vector4::operator = (const Vector4 &v)
{
	this->set(v);
    return *this;
}

Vector4 Vector4::operator - () const
{
    return Vector4(-x, -y, -z, -w);
}
