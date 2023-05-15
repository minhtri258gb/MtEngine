#ifndef __MT_VECTOR_2_H__
#define __MT_VECTOR_2_H__

namespace mt {

class Vector2
{
public:

	// Variables
	float x, y;

	// Forwards
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2 &v);
	~Vector2();

	// Natives
	float squareLength() const;
	float length() const;
	Vector2 normalize();
	void set(float x, float y);
	void set(const Vector2 &v);
	bool equal(const Vector2& v, double epsilon = 1e-6) const;

	// Operator
	Vector2 operator + (const Vector2&) const;
	Vector2 operator - (const Vector2&) const;
	Vector2 operator * (float) const;
	Vector2 operator / (float) const;
	float operator * (const Vector2& v) const; // dot product
	const Vector2& operator += (const Vector2&);
	const Vector2& operator -= (const Vector2&);
    const Vector2& operator *= (float);
    const Vector2& operator /= (float);
    float operator [] (unsigned int index) const;
    float& operator [] (unsigned int index);
    bool operator == (const Vector2&) const;
    bool operator != (const Vector2&) const;
	Vector2& operator = (const Vector2&);
	Vector2 operator - () const;

};

}

#endif
