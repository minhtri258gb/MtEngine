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

	template <class T> static inline T max(T a, T b)
	{
		return a > b ? a : b;
	}

	template <class T> static inline T min(T a, T b)
	{
		return a < b ? a : b;
	}

	template <class T> static inline T abs(T n)
	{
		return n < 0 ? -n : n;
	}

	static double toRadian(double degree); // (0 - 360)
	static double toDegree(double radian); // (0 - PI)

};

}

#endif
