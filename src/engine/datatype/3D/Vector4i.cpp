#define __MT_VECTOR_4_INT_CPP__

#include <sstream>
#include <cmath>

#include "Vector4i.h"
#include "../../exception/Exception.h"

using namespace std;
using namespace mt;

Vector4i::Vector4i()
{
	this->set(0, 0, 0, 0);
}

Vector4i::Vector4i(int x, int y, int z, int w)
{
	this->set(x, y, z, w);
}

Vector4i::Vector4i(const Vector4i &v)
{
	this->set(v);
}

Vector4i::~Vector4i()
{
}

float Vector4i::length()
{
	return sqrtf(x*x + y*y + z*z + w*w);
}

void Vector4i::set(int _x, int _y, int _z, int _w)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
}

void Vector4i::set(const Vector4i &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}

int Vector4i::operator [] (unsigned int index) const
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

int& Vector4i::operator [] (unsigned int index)
{
	if (index < 0 || index > 2)
	{
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
	}
	return *(&x + index);
}

bool Vector4i::operator == (const Vector4i& v) const
{
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool Vector4i::operator != (const Vector4i& v) const
{
    return x != v.x || y != v.y || z != v.z || w != v.w;
}

Vector4i& Vector4i::operator = (const Vector4i &v)
{
	this->set(v);
    return *this;
}
