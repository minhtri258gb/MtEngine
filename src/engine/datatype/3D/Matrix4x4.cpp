#define __MT_MATRIX_4X4_CPP__

#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

#include "Math3D.h"
#include "../../exception/Exception.h"
#include "../../exception/MathException.h"

using namespace std;
using namespace mt;


Matrix4x4::Matrix4x4() {
	this->indentity();
}

Matrix4x4::Matrix4x4(	float m00, float m01, float m02, float m03,
						float m04, float m05, float m06, float m07,
						float m08, float m09, float m10, float m11,
						float m12, float m13, float m14, float m15
) {
	this->set(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);
}

Matrix4x4::Matrix4x4(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4) {
	this->set(v1, v2, v3, v4);
}

Matrix4x4::Matrix4x4(const Quaternion& q) {
	this->set(q);
}

Matrix4x4::Matrix4x4(const Matrix4x4 &m) {
	this->set(m);
}

Matrix4x4::Matrix4x4(const Matrix3x3 &m) {
	this->set(m);
}

Matrix4x4::~Matrix4x4() {
}

void Matrix4x4::indentity() {
	m[0] = m[5] = m[10] = m[15] = 1.0f;
	m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.0f;
}

void Matrix4x4::transpose() {
	swap(m[4], m[1]);
	swap(m[8], m[2]);
	swap(m[9], m[6]);
	swap(m[12], m[3]);
	swap(m[13], m[7]);
	swap(m[14], m[11]);
}

float Matrix4x4::determinant() const {
	return m[ 0]*m[ 5]*m[10]*m[15] - m[ 0]*m[ 5]*m[11]*m[14] + m[ 0]*m[ 6]*m[11]*m[13] - m[ 0]*m[ 6]*m[ 9]*m[15]
		 + m[ 0]*m[ 7]*m[ 9]*m[14] - m[ 0]*m[ 7]*m[10]*m[13] - m[ 1]*m[ 6]*m[11]*m[12] + m[ 1]*m[ 6]*m[ 8]*m[15]
		 - m[ 1]*m[ 7]*m[ 8]*m[14] + m[ 1]*m[ 7]*m[10]*m[12] - m[ 1]*m[ 4]*m[10]*m[15] + m[ 1]*m[ 4]*m[11]*m[14]
		 + m[ 2]*m[ 7]*m[ 8]*m[13] - m[ 2]*m[ 7]*m[ 9]*m[12] + m[ 2]*m[ 4]*m[ 9]*m[15] - m[ 2]*m[ 4]*m[11]*m[13]
		 + m[ 2]*m[ 5]*m[11]*m[12] - m[ 2]*m[ 5]*m[ 8]*m[15] - m[ 3]*m[ 4]*m[ 9]*m[14] + m[ 3]*m[ 4]*m[10]*m[13]
		 - m[ 3]*m[ 5]*m[10]*m[12] + m[ 3]*m[ 5]*m[ 8]*m[14] - m[ 3]*m[ 6]*m[ 8]*m[13] + m[ 3]*m[ 6]*m[ 9]*m[12];
}

void Matrix4x4::inverse() {
	const float det = determinant();
	if (det == 0.0f)
		throw MathException("Khong the invert ma tran nay", __FILE__, __LINE__);

	const float invdet = 1.0f / det;

	Matrix4x4 res;
	res.m[ 0] = invdet  * (m[ 5] * (m[10] * m[15] - m[11] * m[14]) + m[ 6] * (m[11] * m[13] - m[ 9] * m[15]) + m[ 7] * (m[ 9] * m[14] - m[10] * m[13]));
	res.m[ 1] = -invdet * (m[ 1] * (m[10] * m[15] - m[11] * m[14]) + m[ 2] * (m[11] * m[13] - m[ 9] * m[15]) + m[ 3] * (m[ 9] * m[14] - m[10] * m[13]));
	res.m[ 2] = invdet  * (m[ 1] * (m[ 6] * m[15] - m[ 7] * m[14]) + m[ 2] * (m[ 7] * m[13] - m[ 5] * m[15]) + m[ 3] * (m[ 5] * m[14] - m[ 6] * m[13]));
	res.m[ 3] = -invdet * (m[ 1] * (m[ 6] * m[11] - m[ 7] * m[10]) + m[ 2] * (m[ 7] * m[ 9] - m[ 5] * m[11]) + m[ 3] * (m[ 5] * m[10] - m[ 6] * m[ 9]));
	res.m[ 4] = -invdet * (m[ 4] * (m[10] * m[15] - m[11] * m[14]) + m[ 6] * (m[11] * m[12] - m[ 8] * m[15]) + m[ 7] * (m[ 8] * m[14] - m[10] * m[12]));
	res.m[ 5] = invdet  * (m[ 0] * (m[10] * m[15] - m[11] * m[14]) + m[ 2] * (m[11] * m[12] - m[ 8] * m[15]) + m[ 3] * (m[ 8] * m[14] - m[10] * m[12]));
	res.m[ 6] = -invdet * (m[ 0] * (m[ 6] * m[15] - m[ 7] * m[14]) + m[ 2] * (m[ 7] * m[12] - m[ 4] * m[15]) + m[ 3] * (m[ 4] * m[14] - m[ 6] * m[12]));
	res.m[ 7] = invdet  * (m[ 0] * (m[ 6] * m[11] - m[ 7] * m[10]) + m[ 2] * (m[ 7] * m[ 8] - m[ 4] * m[11]) + m[ 3] * (m[ 4] * m[10] - m[ 6] * m[ 8]));
	res.m[ 8] = invdet  * (m[ 4] * (m[ 9] * m[15] - m[11] * m[13]) + m[ 5] * (m[11] * m[12] - m[ 8] * m[15]) + m[ 7] * (m[ 8] * m[13] - m[ 9] * m[12]));
	res.m[ 9] = -invdet * (m[ 0] * (m[ 9] * m[15] - m[11] * m[13]) + m[ 1] * (m[11] * m[12] - m[ 8] * m[15]) + m[ 3] * (m[ 8] * m[13] - m[ 9] * m[12]));
	res.m[10] = invdet  * (m[ 0] * (m[ 5] * m[15] - m[ 7] * m[13]) + m[ 1] * (m[ 7] * m[12] - m[ 4] * m[15]) + m[ 3] * (m[ 4] * m[13] - m[ 5] * m[12]));
	res.m[11] = -invdet * (m[ 0] * (m[ 5] * m[11] - m[ 7] * m[ 9]) + m[ 1] * (m[ 7] * m[ 8] - m[ 4] * m[11]) + m[ 3] * (m[ 4] * m[ 9] - m[ 5] * m[ 8]));
	res.m[12] = -invdet * (m[ 4] * (m[ 9] * m[14] - m[10] * m[13]) + m[ 5] * (m[10] * m[12] - m[ 8] * m[14]) + m[ 6] * (m[ 8] * m[13] - m[ 9] * m[12]));
	res.m[13] = invdet  * (m[ 0] * (m[ 9] * m[14] - m[10] * m[13]) + m[ 1] * (m[10] * m[12] - m[ 8] * m[14]) + m[ 2] * (m[ 8] * m[13] - m[ 9] * m[12]));
	res.m[14] = -invdet * (m[ 0] * (m[ 5] * m[14] - m[ 6] * m[13]) + m[ 1] * (m[ 6] * m[12] - m[ 4] * m[14]) + m[ 2] * (m[ 4] * m[13] - m[ 5] * m[12]));
	res.m[15] = invdet  * (m[ 0] * (m[ 5] * m[10] - m[ 6] * m[ 9]) + m[ 1] * (m[ 6] * m[ 8] - m[ 4] * m[10]) + m[ 2] * (m[ 4] * m[ 9] - m[ 5] * m[ 8]));
	*this = res;
}

bool Matrix4x4::isIdentity() const {
	// Use a small epsilon to solve floating-point inaccuracies
	const static float epsilon = 10e-3f;

	return (m[ 1] <= epsilon && m[ 1] >= -epsilon &&
			m[ 2] <= epsilon && m[ 2] >= -epsilon &&
			m[ 3] <= epsilon && m[ 3] >= -epsilon &&
			m[ 4] <= epsilon && m[ 4] >= -epsilon &&
			m[ 6] <= epsilon && m[ 6] >= -epsilon &&
			m[ 7] <= epsilon && m[ 7] >= -epsilon &&
			m[ 8] <= epsilon && m[ 8] >= -epsilon &&
			m[ 9] <= epsilon && m[ 9] >= -epsilon &&
			m[11] <= epsilon && m[11] >= -epsilon &&
			m[12] <= epsilon && m[12] >= -epsilon &&
			m[13] <= epsilon && m[13] >= -epsilon &&
			m[14] <= epsilon && m[14] >= -epsilon &&
			m[ 0] <= 1.f+epsilon && m[ 0] >= 1.f-epsilon &&
			m[ 5] <= 1.f+epsilon && m[ 5] >= 1.f-epsilon &&
			m[10] <= 1.f+epsilon && m[10] >= 1.f-epsilon &&
			m[15] <= 1.f+epsilon && m[15] >= 1.f-epsilon);
}

void Matrix4x4::perspective(float fovDeg, float aspect, float near, float far) {
	const float tanHalfFovy = tanf(fovDeg / 2.0f);
	m[0] = 1.0f / (aspect * tanHalfFovy);
	m[5] = 1.0f / (tanHalfFovy);
	m[10] = - (far + near) / (far - near);
	m[11] = - 1.0f;
	m[14] = - (2.0f * far * near) / (far - near);
	m[15] = 0.0f;
}

void Matrix4x4::ortho(float left, float right, float bottom, float top) { // , float zNear, float zFar
	m[ 0] = 2.0f / (right - left);
	m[ 5] = 2.0f / (top - bottom);
	m[10] = - 1; // - 2.0f / (zFar - zNear);
	m[12] = - (right + left) / (right - left);
	m[13] = - (top + bottom) / (top - bottom);
	// m[14] = - (zFar + zNear) / (zFar - zNear);
}

void Matrix4x4::lookAt(const Vector3& eye, const Vector3& center, const Vector3& up) {
	vec3 f = (center - eye).normalize();
	vec3 s = (f ^ up).normalize();
	vec3 u = s ^ f;

	m[0] =  s.x;
	m[1] =  u.x;
	m[2] = -f.x;
	m[4] =  s.y;
	m[5] =  u.y;
	m[6] = -f.y;
	m[8] =  s.z;
	m[9] =  u.z;
	m[10] = -f.z;
	m[12] = -(s * eye);
	m[13] = -(u * eye);
	m[14] =  (f * eye);
}

void Matrix4x4::transform(Vector3 position, Quaternion rotation, Vector3 scaling) {
	Matrix3x3 r(rotation);

	m[ 0] = r[0] * scaling.x;
	m[ 1] = r[1] * scaling.x;
	m[ 2] = r[2] * scaling.x;
	m[ 3] = position.x;

	m[ 4] = r[3] * scaling.y;
	m[ 5] = r[4] * scaling.y;
	m[ 6] = r[5] * scaling.y;
	m[ 7] = position.y;

	m[ 8] = r[6] * scaling.z;
	m[ 9] = r[7] * scaling.z;
	m[10] = r[8] * scaling.z;
	m[11]= position.z;

	m[12] = m[13] = m[14] = 0.0f;
	m[15] = 1.0f;
}

void Matrix4x4::translate(const Vector3& v) {
	m[12] = m[ 0] * v[0] + m[ 4] * v[1] + m[ 8] * v[2] + m[12];
	m[13] = m[ 1] * v[0] + m[ 5] * v[1] + m[ 9] * v[2] + m[13];
	m[14] = m[ 2] * v[0] + m[ 6] * v[1] + m[10] * v[2] + m[14];
	m[15] = m[ 3] * v[0] + m[ 7] * v[1] + m[11] * v[2] + m[15];
}

void Matrix4x4::rotationX(float angle) {
	m[5] =  m[10] = cosf(angle);
	m[6] = -(m[9] = sinf(angle));
}

void Matrix4x4::rotationY(float angle) {
	m[0] =  m[10] = cosf(angle);
	m[8] = -(m[2] = sinf(angle));
}

void Matrix4x4::rotationZ(float angle) {
	m[0] =   m[5] = cos(angle);
	m[1] = -(m[4] = sin(angle));
}

void Matrix4x4::rotation(float angle, const Vector3& axis) {
	float c = cosf(angle), s = sinf(angle), t = 1 - c;
	float x = axis.x, y = axis.y, z = axis.z;

	m[ 0] = t*x*x + c;
	m[ 1] = t*x*y - s*z;
	m[ 2] = t*x*z + s*y;

	m[ 4] = t*x*y + s*z;
	m[ 5] = t*y*y + c;
	m[ 6] = t*y*z - s*x;

	m[ 8] = t*x*z - s*y;
	m[ 9] = t*y*z + s*x;
	m[10] = t*z*z + c;

	m[ 3] = m[ 7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	m[15] = 1.0f;
}

void Matrix4x4::rotate(const Quaternion& angle) {
	*this *= mat4(angle); // #TODO optimize
}

void Matrix4x4::scale(float f) {
	this->scale(vec3(f,f,f));
}

void Matrix4x4::scale(const Vector3& v) {
	m[0] *= v[0];
	m[1] *= v[0];
	m[2] *= v[0];
	m[3] *= v[0];
	
	m[4] *= v[1];
	m[5] *= v[1];
	m[6] *= v[1];
	m[7] *= v[1];
	
	m[8] *= v[2];
	m[9] *= v[2];
	m[10] *= v[2];
	m[11] *= v[2];
}

void Matrix4x4::fromEulerAnglesXYZ(float x, float y, float z) {
	float cx = cosf(x);
	float sx = sinf(x);
	float cy = cosf(y);
	float sy = sinf(y);
	float cz = cosf(z);
	float sz = sinf(z);

	// mz*my*mx
	m[ 0] = cz * cy;
	m[ 1] = cz * sy * sx - sz * cx;
	m[ 2] = sz * sx + cz * sy * cx;

	m[ 4] = sz * cy;
	m[ 5] = cz * cx + sz * sy * sx;
	m[ 6] = sz * sy * cx - cz * sx;

	m[ 8] = -sy;
	m[ 9] = cy * sx;
	m[10] = cy * cx;
}

void Matrix4x4::fromToMatrix(const Vector3& from, const Vector3& to) {
	Matrix3x3 m3;
	m3.fromToMatrix(from, to);
	set(m3);
}

void Matrix4x4::decompose(Vector3& position, Quaternion& rotation, Vector3& scaling) const {
	position.x = m[3];
	position.y = m[7];
	position.z = m[11];

	Vector3 vCols0(m[0], m[4], m[ 8]);
	Vector3 vCols1(m[1], m[5], m[ 9]);
	Vector3 vCols2(m[2], m[6], m[10]);
	
	scaling.x = vCols0.length();
	scaling.y = vCols1.length();
	scaling.z = vCols2.length();
	
	if (determinant() < 0)
		scaling = -scaling;
	if (scaling.x)
		vCols0 /= scaling.x;
	if (scaling.y)
		vCols1 /= scaling.y;
	if (scaling.z)
		vCols2 /= scaling.z;

	// build a 3x3 rotation matrix
	Matrix3x3 m(vCols0.x,vCols1.x,vCols2.x,
		vCols0.y,vCols1.y,vCols2.y,
		vCols0.z,vCols1.z,vCols2.z);

	// and generate the rotation quaternion from it
	rotation = Quaternion(m);
}

void Matrix4x4::decompose(Vector3& position, Quaternion& rotation) const {
	// const Matrix4x4& _this = *this;
	
	position.x = m[3];
	position.y = m[7];
	position.z = m[11];

	// extract rotation
	rotation = Quaternion(Matrix3x3(*this));
}

void Matrix4x4::set(	float m00, float m01, float m02, float m03,
						float m04, float m05, float m06, float m07,
						float m08, float m09, float m10, float m11,
						float m12, float m13, float m14, float m15
) {
	m[ 0] = m00; m[ 1] = m01; m[ 2] = m02; m[ 3] = m03;
	m[ 4] = m04; m[ 5] = m05; m[ 6] = m06; m[ 7] = m07;
	m[ 8] = m08; m[ 9] = m09; m[10] = m10; m[11] = m11;
	m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
}

void Matrix4x4::set(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4) {
	m[ 0] = v1.x; m[ 1] = v1.y; m[ 2] = v1.z; m[ 3] = v1.w;
	m[ 4] = v2.x; m[ 5] = v2.y; m[ 6] = v2.z; m[ 7] = v2.w;
	m[ 8] = v3.x; m[ 9] = v3.y; m[10] = v3.z; m[11] = v3.w;
	m[12] = v4.x; m[13] = v4.y; m[14] = v4.z; m[15] = v4.w;
}

void Matrix4x4::set(const Quaternion& q) {
	set(mat3(q));
}

void Matrix4x4::set(const Matrix4x4 &_m) {
	for (int i=0; i<16; i++)
		this->m[i] = _m.m[i];
}

void Matrix4x4::set(const Matrix3x3 &_m) {
	m[0] = _m[0]; m[1] = _m[1]; m[ 2] = _m[2];
	m[4] = _m[3]; m[5] = _m[4]; m[ 6] = _m[5];
	m[8] = _m[6]; m[9] = _m[7]; m[10] = _m[8];
	m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	m[15] = 1.0f;
}

bool Matrix4x4::equal(const Matrix4x4& r, double epsilon) const {
	return
		abs(m[ 0] - r.m[ 0]) <= epsilon &&
		abs(m[ 1] - r.m[ 1]) <= epsilon &&
		abs(m[ 2] - r.m[ 2]) <= epsilon &&
		abs(m[ 3] - r.m[ 3]) <= epsilon &&
		abs(m[ 4] - r.m[ 4]) <= epsilon &&
		abs(m[ 5] - r.m[ 5]) <= epsilon &&
		abs(m[ 6] - r.m[ 6]) <= epsilon &&
		abs(m[ 7] - r.m[ 7]) <= epsilon &&
		abs(m[ 8] - r.m[ 8]) <= epsilon &&
		abs(m[ 9] - r.m[ 9]) <= epsilon &&
		abs(m[10] - r.m[10]) <= epsilon &&
		abs(m[11] - r.m[11]) <= epsilon &&
		abs(m[12] - r.m[12]) <= epsilon &&
		abs(m[13] - r.m[13]) <= epsilon &&
		abs(m[14] - r.m[14]) <= epsilon &&
		abs(m[15] - r.m[15]) <= epsilon;
}

Matrix3x3 Matrix4x4::toMat3() const {
	return Matrix3x3(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
}

Vector3 Matrix4x4::operator * (const Vector3& v) const {
	Vector3 res;
	res.x = m[0] * v.x + m[1] * v.y + m[ 2] * v.z + m[ 3];
	res.y = m[4] * v.x + m[5] * v.y + m[ 6] * v.z + m[ 7];
	res.z = m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11];
	return res;
}

Matrix4x4 Matrix4x4::operator * (const float& f) const {
	Matrix4x4 temp(
		m[ 0] * f, m[ 1] * f, m[ 2] * f, m[ 3] * f,
		m[ 4] * f, m[ 5] * f, m[ 6] * f, m[ 7] * f,
		m[ 8] * f, m[ 9] * f, m[10] * f, m[11] * f,
		m[12] * f, m[13] * f, m[14] * f, m[15] * f);
	return temp;
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4& r) const {
	Matrix4x4 temp(*this);
	temp *= r;
	return temp;
}

Matrix4x4 Matrix4x4::operator + (const Matrix4x4& r) const {
	Matrix4x4 temp(
		r.m[ 0] + m[ 0], r.m[ 1] + m[ 1], r.m[ 2] + m[ 2], r.m[ 3] + m[ 3],
		r.m[ 4] + m[ 4], r.m[ 5] + m[ 5], r.m[ 6] + m[ 6], r.m[ 7] + m[ 7],
		r.m[ 8] + m[ 8], r.m[ 9] + m[ 9], r.m[10] + m[10], r.m[11] + m[11],
		r.m[12] + m[12], r.m[13] + m[13], r.m[14] + m[14], r.m[15] + m[15]);
	return temp;
}

Matrix4x4& Matrix4x4::operator *= (const Matrix4x4& r) {
	this->set(
		m[ 0] * r.m[ 0] + m[ 4] * r.m[ 1] + m[ 8] * r.m[ 2] + m[12] * r.m[ 3],
		m[ 1] * r.m[ 0] + m[ 5] * r.m[ 1] + m[ 9] * r.m[ 2] + m[13] * r.m[ 3],
		m[ 2] * r.m[ 0] + m[ 6] * r.m[ 1] + m[10] * r.m[ 2] + m[14] * r.m[ 3],
		m[ 3] * r.m[ 0] + m[ 7] * r.m[ 1] + m[11] * r.m[ 2] + m[15] * r.m[ 3],
		m[ 0] * r.m[ 4] + m[ 4] * r.m[ 5] + m[ 8] * r.m[ 6] + m[12] * r.m[ 7],
		m[ 1] * r.m[ 4] + m[ 5] * r.m[ 5] + m[ 9] * r.m[ 6] + m[13] * r.m[ 7],
		m[ 2] * r.m[ 4] + m[ 6] * r.m[ 5] + m[10] * r.m[ 6] + m[14] * r.m[ 7],
		m[ 3] * r.m[ 4] + m[ 7] * r.m[ 5] + m[11] * r.m[ 6] + m[15] * r.m[ 7],
		m[ 0] * r.m[ 8] + m[ 4] * r.m[ 9] + m[ 8] * r.m[10] + m[12] * r.m[11],
		m[ 1] * r.m[ 8] + m[ 5] * r.m[ 9] + m[ 9] * r.m[10] + m[13] * r.m[11],
		m[ 2] * r.m[ 8] + m[ 6] * r.m[ 9] + m[10] * r.m[10] + m[14] * r.m[11],
		m[ 3] * r.m[ 8] + m[ 7] * r.m[ 9] + m[11] * r.m[10] + m[15] * r.m[11],
		m[ 0] * r.m[12] + m[ 4] * r.m[13] + m[ 8] * r.m[14] + m[12] * r.m[15],
		m[ 1] * r.m[12] + m[ 5] * r.m[13] + m[ 9] * r.m[14] + m[13] * r.m[15],
		m[ 2] * r.m[12] + m[ 6] * r.m[13] + m[10] * r.m[14] + m[14] * r.m[15],
		m[ 3] * r.m[12] + m[ 7] * r.m[13] + m[11] * r.m[14] + m[15] * r.m[15]);
	return *this;
}

bool Matrix4x4::operator == (const Matrix4x4& m) const {
	return (m[ 0] == m.m[ 0] && m[ 1] == m.m[ 1] && m[ 2] == m.m[ 2] && m[ 3] == m.m[ 3] &&
			m[ 4] == m.m[ 4] && m[ 5] == m.m[ 5] && m[ 6] == m.m[ 6] && m[ 7] == m.m[ 7] &&
			m[ 8] == m.m[ 8] && m[ 9] == m.m[ 9] && m[10] == m.m[10] && m[11] == m.m[11] &&
			m[12] == m.m[12] && m[13] == m.m[13] && m[14] == m.m[14] && m[15] == m.m[15]);
}

bool Matrix4x4::operator != (const Matrix4x4& m) const {
	return !(*this == m);
}

float Matrix4x4::operator [] (unsigned int index) const {
	if (index < 0 || index > 15)
	{
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error("INDEX_INVAIL", err_msg.str());
	}
	return this->m[index];
}

float& Matrix4x4::operator [] (unsigned int index) {
	if (index < 0 || index > 15) {
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error("INDEX_INVAIL", err_msg.str());
	}
	return *(&m[0] + index);
}
