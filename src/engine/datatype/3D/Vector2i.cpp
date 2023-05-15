#define __MT_VECTOR_2_INT_CPP__

#include <sstream>
#include <cmath>

#include "Vector2i.h"
#include "../../exception/Exception.h"

using namespace std;
using namespace mt;

Vector2i::Vector2i()
{
	this->set(0, 0);
}

Vector2i::Vector2i(int x, int y)
{
	this->set(x, y);
}

Vector2i::Vector2i(const Vector2i &v)
{
	this->set(v);
}

Vector2i::~Vector2i()
{
}

float Vector2i::squareLength() const
{
	return x*x + y*y;
}

float Vector2i::length() const
{
	return sqrtf(x*x + y*y);
}

void Vector2i::set(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
}

void Vector2i::set(const Vector2i &v)
{
	this->x = v.x;
	this->y = v.y;
}

int Vector2i::operator [] (unsigned int index) const
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

int& Vector2i::operator [] (unsigned int index)
{
	if (index < 0 || index > 2)
	{
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
	}
	return *(&x + index);
}

bool Vector2i::operator == (const Vector2i& v) const
{
    return x == v.x && y == v.y;
}

bool Vector2i::operator != (const Vector2i& v) const
{
    return x != v.x || y != v.y;
}

Vector2i& Vector2i::operator = (const Vector2i &v)
{
	this->set(v);
    return *this;
}
