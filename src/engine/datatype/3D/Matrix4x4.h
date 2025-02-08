#ifndef __MT_MATRIX_4X4_H__
#define __MT_MATRIX_4X4_H__

#include "Vector4.h"
#include "Matrix3x3.h"

namespace mt {

class Quaternion;

class Matrix4x4 {
public:

	// Forwards
	Matrix4x4();
	Matrix4x4(float m00, float m01, float m02, float m03,
						float m04, float m05, float m06, float m07,
						float m08, float m09, float m10, float m11,
						float m12, float m13, float m14, float m15);
	Matrix4x4(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4);
	Matrix4x4(const Quaternion&);
	Matrix4x4(const Matrix3x3&);
	Matrix4x4(const Matrix4x4&);
	~Matrix4x4();

	// Natives
	void indentity();
	void transpose();
	float determinant() const;
	void inverse();
	bool isIdentity() const;

	// Proj Matrix
	void perspective(float fovDeg, float screenRatio, float near, float far);
	void ortho(float left, float right, float bottom, float top); // , float zNear, float zFar

	// View matrix
	void lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

	// Model matrix
	void transform(Vector3 position, Quaternion rotation, Vector3 scaling);
	void translate(const Vector3&);
	void rotationX(float angle);
	void rotationY(float angle);
	void rotationZ(float angle);
	void rotation(float angle, const Vector3& axis);
	void rotate(const Quaternion& angle);
	void scale(float factor);
	void scale(const Vector3& scaleFactor);

	void fromEulerAnglesXYZ(float x, float y, float z);
	void fromToMatrix(const Vector3& from, const Vector3& to);

	void decompose(Vector3& position, Quaternion& rotation, Vector3& scaling) const;
	void decompose(Vector3& position, Quaternion& rotation) const;

	void set(	float m00, float m01, float m02, float m03,
						float m04, float m05, float m06, float m07,
						float m08, float m09, float m10, float m11,
						float m12, float m13, float m14, float m15);
	void set(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4);
	void set(const Quaternion&);
	void set(const Matrix4x4 &m);
	void set(const Matrix3x3 &m);
	bool equal(const Matrix4x4& r, double epsilon = 1e-6) const;
	Matrix3x3 toMat3() const;

	// Operator
	Vector3 operator * (const Vector3&) const;
	Matrix4x4 operator * (const float&) const;
	Matrix4x4 operator * (const Matrix4x4&) const;
	Matrix4x4 operator + (const Matrix4x4&) const;
	Matrix4x4& operator *= (const Matrix4x4&);
	bool operator == (const Matrix4x4&) const;
	bool operator != (const Matrix4x4&) const;
	float operator [] (unsigned int index) const;
	float& operator [] (unsigned int index);

private:

	// Variable
	float m[16];

};

}

#endif
