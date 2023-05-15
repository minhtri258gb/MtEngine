#ifndef __MT_MATRIX_3X3_H__
#define __MT_MATRIX_3X3_H__

namespace mt {

class Matrix4x4;
class Quaternion;

class Matrix3x3
{
public:

	// Forwards
	Matrix3x3();
	Matrix3x3(	float m0, float m1, float m2,
				float m3, float m4, float m5,
				float m6, float m7, float m8);
	Matrix3x3(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	Matrix3x3(const Matrix3x3&);
	Matrix3x3(const Matrix4x4&);
	Matrix3x3(const Quaternion&);
	~Matrix3x3();

	// Natives
	void indentity();
	Matrix3x3& transpose();
	float determinant() const;
	Matrix3x3& inverse();
	void rotationZ(float angle);
	void rotation(float angle, const Vector3& axis);
	void translation(const Vector2& v);
	Matrix3x3 fromToMatrix(const Vector3& from, const Vector3& to);
	void set(	float m0, float m1, float m2,
				float m3, float m4, float m5,
				float m6, float m7, float m8);
	void set(Vector3 v1, Vector3 v2, Vector3 v3);
	void set(const Matrix3x3&);
	void set(const Matrix4x4&);
	void set(const Quaternion&);
	bool equal(const Matrix3x3& r, double epsilon = 1e-6) const;

	// Operator
	Vector3 operator * (const Vector3&) const;
	Matrix3x3 operator * (const Matrix3x3&) const;
	Matrix3x3& operator *= (const Matrix3x3&);
	bool operator == (const Matrix3x3&) const;
	bool operator != (const Matrix3x3&) const;
    float operator [] (unsigned int index) const;
	float& operator [] (unsigned int index);

private:

	// Variable
	float m[9];

};

}

#endif
