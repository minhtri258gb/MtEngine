#ifndef __MT_VECTOR_4_INT_H__
#define __MT_VECTOR_4_INT_H__

#include "Vector3i.h"

namespace mt {

class Vector4i : public Vector3i
{
public:

	// Variables
	int w;

	// Forwards
	Vector4i();
	Vector4i(int x, int y, int z, int w);
	Vector4i(const Vector4i &v);
	~Vector4i();

	// Natives
	float length();
	void set(int x, int y, int z, int w);
	void set(const Vector4i &v);

	// Operator
    int operator [] (unsigned int index) const;
    int& operator [] (unsigned int index);
    bool operator == (const Vector4i& v) const;
    bool operator != (const Vector4i& v) const;
	Vector4i& operator = (const Vector4i &v);

};

}

#endif
