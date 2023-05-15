#ifndef __MT_VECTOR_3_INT_H__
#define __MT_VECTOR_3_INT_H__

#include "Vector2i.h"

namespace mt {

class Vector3i : public Vector2i
{
public:

	// Variables
	int z;

	// Forwards
	Vector3i();
	Vector3i(int x, int y, int z);
	Vector3i(const Vector3i &v);
	~Vector3i();

	// Natives
	float length();
	void set(int x, int y, int z);
	void set(const Vector3i &v);

	// Operator
    int operator [] (unsigned int index) const;
    int& operator [] (unsigned int index);
    bool operator == (const Vector3i& v) const;
    bool operator != (const Vector3i& v) const;
	Vector3i& operator = (const Vector3i &v);

};

}

#endif
