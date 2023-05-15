#ifndef __MT_VECTOR_3_H__
#define __MT_VECTOR_3_H__

#include "Vector2.h"

namespace mt {

class Quaternion;

class Vector3 : public Vector2
{
public:

	// Variables
	float z;

	// Forwards
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3 &v);
	~Vector3();

	// Natives
	float squareLength() const;
	float length() const;
	Vector3 normalize();
	Vector3 rotate(const Quaternion&);
	void set(float x, float y, float z);
	void set(const Vector3 &v);
	bool equal(const Vector3& v, double epsilon = 1e-6) const;
	Vector3 mix(const Vector3& v, float factor);

	// Operator
	Vector3 operator + (const Vector3&) const;
	Vector3 operator - (const Vector3&) const;
	Vector3 operator * (float) const;
	Vector3 operator / (float) const;
	float operator * (const Vector3&) const; // dot product
	Vector3 operator ^ (const Vector3&) const; // cross product
	const Vector3& operator += (const Vector3& v);
	const Vector3& operator -= (const Vector3& v);
    const Vector3& operator *= (float f);
    const Vector3& operator /= (float f);
	bool operator == (const Vector3&) const;
	bool operator != (const Vector3&) const;
    float operator [] (unsigned int index) const;
    float& operator [] (unsigned int index);
	Vector3& operator = (const Vector3 &v);
	Vector3 operator - ();

};

}

#endif
