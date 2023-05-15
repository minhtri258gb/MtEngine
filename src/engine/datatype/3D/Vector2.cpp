#define __MT_VECTOR_2_CPP__

#include <sstream>
#include <cmath>

#include "Vector2.h"
#include "../../exception/Exception.h"

using namespace std;
using namespace mt;

Vector2::Vector2()
{
	this->set(0.0f, 0.0f);
}

Vector2::Vector2(float x, float y)
{
	this->set(x, y);
}

Vector2::Vector2(const Vector2 &v)
{
	this->set(v);
}

Vector2::~Vector2()
{
}

float Vector2::squareLength() const
{
	return x*x + y*y;
}

float Vector2::length() const
{
	return sqrtf(x*x + y*y);
}

Vector2 Vector2::normalize()
{
    return *this / length();
}

void Vector2::set(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
}

void Vector2::set(const Vector2 &v)
{
	this->x = v.x;
	this->y = v.y;
}

bool Vector2::equal(const Vector2& v, double epsilon) const
{
    return
        abs(x - v.x) <= epsilon &&
        abs(y - v.y) <= epsilon;
}

Vector2 Vector2::operator + (const Vector2& v) const
{
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator - (const Vector2& v) const
{
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator * (float f) const
{
    return Vector2(x*f, y*f);
}

Vector2 Vector2::operator / (float f) const
{
    return Vector2(x/f, y/f);
}

float Vector2::operator * (const Vector2& v) const
{
	return x * v.x + y * v.y;
}

const Vector2& Vector2::operator += (const Vector2& v)
{
    x += v.x;
	y += v.y;
    return *this;
}

const Vector2& Vector2::operator -= (const Vector2& v)
{
    x -= v.x;
	y -= v.y;
    return *this;
}

const Vector2& Vector2::operator *= (float f)
{
    x *= f;
	y *= f;
    return *this;
}

const Vector2& Vector2::operator /= (float f)
{
    x /= f;
	y /= f;
    return *this;
}

float Vector2::operator [] (unsigned int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	default:
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
    }
}

float& Vector2::operator [] (unsigned int index)
{
	if (index < 0 || index > 2)
	{
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
	}
	return *(&x + index);
}

bool Vector2::operator == (const Vector2& v) const
{
	return  x == v.x && y == v.y;
}

bool Vector2::operator != (const Vector2& v) const
{
	return x != v.x || y != v.y;
}

Vector2& Vector2::operator = (const Vector2 &v)
{
	this->set(v);
    return *this;
}

Vector2 Vector2::operator - () const
{
    return Vector2(-x, -y);
}
