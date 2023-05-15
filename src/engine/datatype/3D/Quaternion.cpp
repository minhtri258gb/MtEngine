#define __MT_QUATERNION_CPP__

#include <sstream>
#include <cmath>
#include <limits>

#include "Math3D.h"
#include "../../exception/BoundingException.h"

using namespace std;
using namespace mt;

Quaternion::Quaternion()
{
	set(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	set(x, y, z, w);
}

Quaternion::Quaternion(float pitch, float yaw, float roll)
{
	set(pitch, yaw, roll);
}

Quaternion::Quaternion(float angle, Vector3 axis)
{
	set(angle, axis);
}

Quaternion::Quaternion(Vector3 normalized)
{
	set(normalized);
}

Quaternion::Quaternion(const Vector4& v)
{
	set(v);
}

Quaternion::Quaternion(const Matrix3x3& m)
{
	set(m);
}

Quaternion::Quaternion(const Quaternion &q)
{
	set(q);
}

Quaternion::~Quaternion()
{
}

Quaternion Quaternion::normalize() const
{
	float l = length();
	return Quaternion(x/l, y/l, z/l, w/l);
}

Quaternion Quaternion::conjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::interpolate(const Quaternion& start, const Quaternion& end, float factor)
{
	// calc cosine theta
	float cosom = start.x * end.x + start.y * end.y + start.z * end.z + start.w * end.w;

	// adjust signs (if necessary)
	Quaternion endTmp = end;
	if (cosom < 0.0f)
	{
		cosom = -cosom;
		endTmp.x = -endTmp.x; // Reverse all signs
		endTmp.y = -endTmp.y;
		endTmp.z = -endTmp.z;
		endTmp.w = -endTmp.w;
	}

	// Calculate coefficients
	float sclp, sclq;
	if ((1.0f - cosom) > 0.0001f) // 0.0001 -> some epsillon
	{
		// Standard case (slerp)
		float omega, sinom;
		omega = acosf(cosom); // extract theta from dot product's cos theta
		sinom = sinf(omega);
		sclp  = sinf((1.0f - factor) * omega) / sinom;
		sclq  = sinf(factor * omega) / sinom;
	} else
	{
		// Very close, do linear interp (because it's faster)
		sclp = 1.0f - factor;
		sclq = factor;
	}

	return Quaternion(
		sclp * start.x + sclq * endTmp.x,
		sclp * start.y + sclq * endTmp.y,
		sclp * start.z + sclq * endTmp.z,
		sclp * start.w + sclq * endTmp.w
	);
}

void Quaternion::set(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void Quaternion::set(float pitch, float yaw, float roll)
{
	const float fSinPitch(sinf(pitch * 0.5f));
	const float fCosPitch(cosf(pitch * 0.5f));
	const float fSinYaw(sinf(yaw * 0.5f));
	const float fCosYaw(cosf(yaw * 0.5f));
	const float fSinRoll(sinf(roll * 0.5f));
	const float fCosRoll(cosf(roll * 0.5f));
	const float fCosPitchCosYaw(fCosPitch * fCosYaw);
	const float fSinPitchSinYaw(fSinPitch * fSinYaw);
	x = fSinRoll * fCosPitchCosYaw     - fCosRoll * fSinPitchSinYaw;
	y = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
	z = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
	w = fCosRoll * fCosPitchCosYaw     + fSinRoll * fSinPitchSinYaw;
}

void Quaternion::set(float angle, Vector3 axis)
{
	axis = axis.normalize();
	angle /= 2.0f;
	const float sin_a = sinf(angle);
	x = axis.x * sin_a;
	y = axis.y * sin_a;
	z = axis.z * sin_a;
	w = cosf(angle);
}

void Quaternion::set(Vector3 normalized)
{
	x = normalized.x;
	y = normalized.y;
	z = normalized.z;

	const float t = 1.0f - (x*x) - (y*y) - (z*z);

	if (t < 0.0f)
		w = 0.0f;
	else
		w = sqrtf(t);
}

void Quaternion::set(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

void Quaternion::set(const Matrix3x3& m)
{
	float t = m[0] + m[4] + m[8];

	// large enough
	if (t > 0.0f)
	{
		float s = sqrtf(1 + t) * 2.0f;
		x = (m[7] - m[5]) / s;
		y = (m[2] - m[6]) / s;
		z = (m[3] - m[1]) / s;
		w = 0.25f * s;
	} // else we have to check several cases
	else if (m[0] > m[4] && m[0] > m[8])
	{
		// Column 0:
		float s = sqrtf(1.0f + m[0] - m[4] - m[8]) * 2.0f;
		x = 0.25f * s;
		y = (m[3] + m[1]) / s;
		z = (m[2] + m[6]) / s;
		w = (m[7] - m[5]) / s;
	}
	else if( m[4] > m[8])
	{
		// Column 1:
		float s = sqrtf(1.0f + m[4] - m[0] - m[8]) * 2.0f;
		x = (m[3] + m[1]) / s;
		y = 0.25f * s;
		z = (m[7] + m[5]) / s;
		w = (m[2] - m[6]) / s;
	} else
	{
		// Column 2:
		float s = sqrtf(1.0f + m[8] - m[0] - m[4]) * 2.0f;
		x = (m[2] + m[6]) / s;
		y = (m[7] + m[5]) / s;
		z = 0.25f * s;
		w = (m[3] - m[1]) / s;
	}
}

void Quaternion::set(const Quaternion &q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

bool Quaternion::equal(const Quaternion& v, double epsilon) const
{
	return
		abs(x - v.x) <= epsilon &&
		abs(y - v.y) <= epsilon &&
		abs(z - v.z) <= epsilon &&
		abs(w - v.w) <= epsilon;
}

Quaternion Quaternion::slerp(const Quaternion& q, float factor)
{
	quat x = *this;
	quat z = q;

	float cosTheta = x * q;

	if (cosTheta < 0.0f)
	{
		z = -q;
		cosTheta = -cosTheta;
	}

	if (cosTheta > 1.0f - numeric_limits<float>::epsilon())
	{
		// Linear interpolation
		return quat(x.x + (z.x - x.x) * factor,
					x.y + (z.y - x.y) * factor,
					x.z + (z.z - x.z) * factor,
					x.w + (z.w - x.w) * factor);
	}
	else
	{
		// Essential Mathematics, page 467
		float angle = acos(cosTheta);
		return (x * sin((1.0f - factor) * angle) + z * sin(factor * angle)) / sin(angle);
	}
}

float Quaternion::operator * (const Quaternion& q) const
{
	return x * q.x + y * q.y + z * q.z + w * q.w;
}

Quaternion Quaternion::operator * (float f) const
{
	return Quaternion(x*f, y*f, z*f, w*f);
}

Quaternion Quaternion::operator ^ (const Quaternion& q) const
{
	return Quaternion(
		w*q.x + x*q.w + y*q.z - z*q.y,
		w*q.y + y*q.w + z*q.x - x*q.z,
		w*q.z + z*q.w + x*q.y - y*q.x,
		w*q.w - x*q.x - y*q.y - z*q.z
	);
}

bool Quaternion::operator == (const Quaternion& q) const
{
	return x == q.x && y == q.y && z == q.z && w == q.w;
}

bool Quaternion::operator != (const Quaternion& q) const
{
	return x != q.x || y != q.y || z != q.z || w != q.w;
}
