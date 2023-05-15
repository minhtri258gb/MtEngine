#ifndef __MT_NATH_H__
#define __MT_NATH_H__

#ifndef PI
#define PI 3.1415926535
#endif

namespace mt
{

class Math
{
public:

	static double toRadian(double degree); // (0 - 360)
	static double toDegree(double radian); // (0 - PI)

};

}

#endif
