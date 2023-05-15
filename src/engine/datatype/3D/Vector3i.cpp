#define __MT_VECTOR_3_INT_CPP__

#include <sstream>
#include <cmath>

#include "Vector3i.h"
#include "../../exception/Exception.h"

using namespace std;
using namespace mt;

Vector3i::Vector3i()
{
	this->set(0, 0, 0);
}

Vector3i::Vector3i(int x, int y, int z)
{
	this->set(x, y, z);
}

Vector3i::Vector3i(const Vector3i &v)
{
	this->set(v);
}

Vector3i::~Vector3i()
{
}

float Vector3i::length()
{
	return sqrtf(x*x + y*y + z*z);
}

void Vector3i::set(int _x, int _y, int _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

void Vector3i::set(const Vector3i &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

int Vector3i::operator [] (unsigned int index) const
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

int& Vector3i::operator [] (unsigned int index)
{
	if (index < 0 || index > 2)
	{
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
	}
	return *(&x + index);
}

bool Vector3i::operator == (const Vector3i& v) const
{
    return x == v.x && y == v.y && z == v.z;
}

bool Vector3i::operator != (const Vector3i& v) const
{
    return x != v.x || y != v.y || z != v.z;
}

Vector3i& Vector3i::operator = (const Vector3i &v)
{
	this->set(v);
    return *this;
}
