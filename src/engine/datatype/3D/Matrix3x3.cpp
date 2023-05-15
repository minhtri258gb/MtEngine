#define __MT_MATRIX_3X3_CPP__

#include <sstream>
#include <cmath>

#include "Math3D.h"
#include "../../exception/Exception.h"
#include "../../exception/MathException.h"

using namespace std;
using namespace mt;

Matrix3x3::Matrix3x3()
{
	this->indentity();
}

Matrix3x3::Matrix3x3(	float m0, float m1, float m2,
						float m3, float m4, float m5,
						float m6, float m7, float m8)
{
	this->set(m1, m1, m2, m3, m4, m5, m6, m7, m8);
}

Matrix3x3::Matrix3x3(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	this->set(v1, v2, v3);
}

Matrix3x3::Matrix3x3(const Matrix3x3& m)
{
	this->set(m);
}

Matrix3x3::Matrix3x3(const Matrix4x4& m)
{
	this->set(m);
}

Matrix3x3::Matrix3x3(const Quaternion& q)
{
    set(q);
}

Matrix3x3::~Matrix3x3()
{
}

void Matrix3x3::indentity()
{
	m[0] = m[4] = m[8] = 1.0f;
	m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
}

Matrix3x3& Matrix3x3::transpose()
{
    swap(m[3], m[1]);
    swap(m[6], m[2]);
    swap(m[7], m[5]);
    return *this;
}

float Matrix3x3::determinant() const
{
    return m[0]*m[4]*m[8] - m[0]*m[5]*m[7] + m[1]*m[5]*m[6] - m[1]*m[3]*m[8] + m[2]*m[3]*m[7] - m[2]*m[4]*m[6];
}

Matrix3x3& Matrix3x3::inverse()
{
    float det = determinant();
    if(det == 0.0f)
		throw MathException("Khong the invert ma tran nay", __FILE__, __LINE__);

    float invdet = 1.0f / det;

	Matrix3x3 res;
	res.m[0] = invdet  * (m[4] * m[8] - m[5] * m[7]);
	res.m[1] = -invdet * (m[1] * m[8] - m[2] * m[7]);
	res.m[2] = invdet  * (m[1] * m[5] - m[2] * m[4]);
	res.m[3] = -invdet * (m[3] * m[8] - m[5] * m[6]);
	res.m[4] = invdet  * (m[0] * m[8] - m[2] * m[6]);
	res.m[5] = -invdet * (m[0] * m[5] - m[2] * m[3]);
	res.m[6] = invdet  * (m[3] * m[7] - m[4] * m[6]);
	res.m[7] = -invdet * (m[0] * m[7] - m[1] * m[6]);
	res.m[8] = invdet  * (m[0] * m[4] - m[1] * m[3]);
	*this = res;

    return *this;
}

void Matrix3x3::rotationZ(float angle)
{
	m[0] = m[4] = cosf(angle);
	m[3] = sinf(angle);
	m[1] = - m[3];
	m[2] = m[5] = m[6] = m[7] = 0.f;
	m[8] = 1.f;
}

void Matrix3x3::rotation(float angle, const Vector3& axis)
{
	float c = cosf(angle), s = sinf(angle), t = 1 - c;
	float x = axis.x, y = axis.y, z = axis.z;

	m[0] = t*x*x + c;   m[1] = t*x*y - s*z; m[2] = t*x*z + s*y;
	m[3] = t*x*y + s*z; m[4] = t*y*y + c;   m[5] = t*y*z - s*x;
	m[6] = t*x*z - s*y; m[7] = t*y*z + s*x; m[8] = t*z*z + c;
}

void Matrix3x3::translation(const Vector2& v)
{
	indentity();
    m[2] = v.x;
    m[5] = v.y;
}

Matrix3x3 Matrix3x3::fromToMatrix(const Vector3& from, const Vector3& to)
{
	Matrix3x3 res;

    const float e = from * to;
    const float f = (e < 0)? -e:e;

    if (f > 1.0f - 0.00001f)
    {
        Vector3 u,v;
        Vector3 x;

        x.x = (from.x > 0.0)? from.x : -from.x;
        x.y = (from.y > 0.0)? from.y : -from.y;
        x.z = (from.z > 0.0)? from.z : -from.z;

        if (x.x < x.y)
        {
            if (x.x < x.z)
            {
                x.x = 1.0f;
                x.y = x.z = 0.0f;
            }
            else
            {
                x.z = 1.0f;
                x.x = x.y = 0.0f;
            }
        }
        else
        {
            if (x.y < x.z)
            {
                x.y = 1.0f;
                x.x = x.z = 0.0f;
            }
            else
            {
                x.z = 1.0f;
                x.x = x.y = 0.0f;
            }
        }

        u.x = x.x - from.x; u.y = x.y - from.y; u.z = x.z - from.z;
        v.x = x.x - to.x;   v.y = x.y - to.y;   v.z = x.z - to.z;

        const float c1_ = 2.0f / (u * u);
        const float c2_ = 2.0f / (v * v);
        const float c3_ = c1_ * c2_  * (u * v);

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                res[i*3+j] =  - c1_ * u[i] * u[j] - c2_ * v[i] * v[j] + c3_ * v[i] * u[j];
            }
            res[i*3+i] += 1.0f;
        }
    }
    else
    {
        const Vector3 v = from ^ to;
        const float h = 1.0f/(1.0f + e);
        const float hvx = h * v.x;
        const float hvz = h * v.z;
        const float hvxy = hvx * v.y;
        const float hvxz = hvx * v.z;
        const float hvyz = hvz * v.y;
        res[0] = e + hvx * v.x;
        res[1] = hvxy - v.z;
        res[2] = hvxz + v.y;

        res[3] = hvxy + v.z;
        res[4] = e + h * v.y * v.y;
        res[5] = hvyz - v.x;

        res[6] = hvxz - v.y;
        res[7] = hvyz + v.x;
        res[8] = e + hvz * v.z;
    }
    return res;
}

void Matrix3x3::set(	float m0, float m1, float m2,
						float m3, float m4, float m5,
						float m6, float m7, float m8)
{
	m[0] = m0; m[1] = m1; m[2] = m2;
	m[3] = m3; m[4] = m4; m[5] = m5;
	m[6] = m6; m[7] = m7; m[8] = m8;
}

void Matrix3x3::set(Vector3 v1, Vector3 v2, Vector3 v3)
{
	m[0] = v1.x; m[1] = v1.y; m[2] = v1.z;
	m[3] = v2.x; m[4] = v2.y; m[5] = v2.z;
	m[6] = v3.x; m[7] = v3.y; m[8] = v3.z;
}

void Matrix3x3::set(const Matrix3x3& _m)
{
	for (int i=0; i<9; i++)
		this->m[i] = _m.m[i];
}

void Matrix3x3::set(const Matrix4x4& _m)
{
    m[0] = _m[0];
    m[1] = _m[1];
    m[2] = _m[2];

    m[3] = _m[4];
    m[4] = _m[5];
    m[5] = _m[6];

    m[6] = _m[8];
    m[7] = _m[9];
    m[8] = _m[10];
}

void Matrix3x3::set(const Quaternion& q)
{
    m[0] = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    m[1] = 2.0f * (q.x * q.y + q.z * q.w);
    m[2] = 2.0f * (q.x * q.z - q.y * q.w);
    m[3] = 2.0f * (q.x * q.y - q.z * q.w);
    m[4] = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
    m[5] = 2.0f * (q.y * q.z + q.x * q.w);
    m[6] = 2.0f * (q.x * q.z + q.y * q.w);
    m[7] = 2.0f * (q.y * q.z - q.x * q.w);
    m[8] = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
}

bool Matrix3x3::equal(const Matrix3x3& r, double epsilon) const
{
	return
        abs(m[0] - r.m[0]) <= epsilon &&
        abs(m[1] - r.m[1]) <= epsilon &&
        abs(m[2] - r.m[2]) <= epsilon &&
        abs(m[3] - r.m[3]) <= epsilon &&
        abs(m[4] - r.m[4]) <= epsilon &&
        abs(m[5] - r.m[5]) <= epsilon &&
        abs(m[6] - r.m[6]) <= epsilon &&
        abs(m[7] - r.m[7]) <= epsilon &&
        abs(m[8] - r.m[8]) <= epsilon;
}

Vector3 Matrix3x3::operator * (const Vector3& v) const
{
    Vector3 res;
    res.x = m[0] * v.x + m[1] * v.y + m[2] * v.z;
    res.y = m[3] * v.x + m[4] * v.y + m[5] * v.z;
    res.z = m[6] * v.x + m[7] * v.y + m[8] * v.z;
    return res;
}

Matrix3x3 Matrix3x3::operator * (const Matrix3x3& m) const
{
    Matrix3x3 temp(*this);
    temp *= m;
    return temp;
}

Matrix3x3& Matrix3x3::operator *= (const Matrix3x3& r)
{
	this->set(
		r.m[0] * m[0] + r.m[3] * m[1] + r.m[6] * m[2],
		r.m[1] * m[0] + r.m[4] * m[1] + r.m[7] * m[2],
		r.m[2] * m[0] + r.m[5] * m[1] + r.m[8] * m[2],
		r.m[0] * m[3] + r.m[3] * m[4] + r.m[6] * m[5],
		r.m[1] * m[3] + r.m[4] * m[4] + r.m[7] * m[5],
		r.m[2] * m[3] + r.m[5] * m[4] + r.m[8] * m[5],
		r.m[0] * m[6] + r.m[3] * m[7] + r.m[6] * m[8],
		r.m[1] * m[6] + r.m[4] * m[7] + r.m[7] * m[8],
		r.m[2] * m[6] + r.m[5] * m[7] + r.m[8] * m[8]
	);
	return *this;
}

bool Matrix3x3::operator == (const Matrix3x3& r) const
{
    return m[0] == r.m[0] && m[1] == r.m[1] && m[2] == r.m[2] &&
           m[3] == r.m[3] && m[4] == r.m[4] && m[5] == r.m[5] &&
           m[6] == r.m[6] && m[7] == r.m[7] && m[8] == r.m[8];
}

bool Matrix3x3::operator != (const Matrix3x3& r) const
{
    return !(*this == r);
}

float Matrix3x3::operator [] (unsigned int index) const
{
	if (index < 0 || index > 8)
	{
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
	}
	return this->m[index];
}

float& Matrix3x3::operator [] (unsigned int index)
{
	if (index < 0 || index > 8)
	{
		stringstream err_msg;
		err_msg << "index = " << index;
		throw error(err_msg.str());
	}
	return *(&m[0] + index);
}
