#ifndef __MT_VECTOR_4_H__
#define __MT_VECTOR_4_H__

#include "Vector3.h"

namespace mt {

class Vector4 : public Vector3
{
public:

	// Variables
	float w;

	// Forwards
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4&);
	~Vector4();

	// Natives
	float squareLength() const;
	float length() const;
	Vector4 normalize();
	void set(float x, float y, float z, float w);
	void set(const Vector4 &v);
	bool equal(const Vector4& v, double epsilon = 1e-6) const;

	// Operator
	Vector4 operator + (const Vector4&) const;
	Vector4 operator - (const Vector4&) const;
	Vector4 operator * (float) const;
	float operator * (const Vector4&) const; // dot product
	Vector4 operator / (float) const;
	const Vector4& operator += (const Vector4& v);
	const Vector4& operator -= (const Vector4& v);
    const Vector4& operator *= (float f);
    const Vector4& operator /= (float f);
    bool operator == (const Vector4&) const;
    bool operator != (const Vector4&) const;
    float operator [] (unsigned int index) const;
    float& operator [] (unsigned int index);
	Vector4& operator = (const Vector4 &v);
	Vector4 operator - () const;

};

}

#endif
