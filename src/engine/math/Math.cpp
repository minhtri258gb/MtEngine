#define __MT_MATH_H__

#include "Math.h"

using namespace mt;

double Math::toRadian(double degree)
{
	return degree / 180.0 * PI;
}

double Math::toDegree(double radian)
{
	return radian / PI * 180.0;
}
