#ifndef __MT_QUATERNION_H__
#define __MT_QUATERNION_H__

namespace mt {

class Quaternion : public Vector4
{
public:

	// Forwards
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(float pitch, float yaw, float roll);
	Quaternion(float angle, Vector3 axis);
	Quaternion(Vector3 normalized);
	Quaternion(const Vector4& v);
	Quaternion(const Matrix3x3& m);
	Quaternion(const Quaternion& q);
	~Quaternion();

	// Natives
	Quaternion normalize() const;
	Quaternion conjugate() const;
	static Quaternion interpolate(const Quaternion& start, const Quaternion& end, float factor);
	void set(float x, float y, float z, float w);
	void set(float pitch, float yaw, float roll);
	void set(float angle, Vector3 axis);
	void set(Vector3 normalized);
	void set(const Vector4& v);
	void set(const Matrix3x3& m);
	void set(const Quaternion& q);
	bool equal(const Quaternion& r, double epsilon = 1e-6) const;
	Quaternion slerp(const Quaternion& q, float factor);

	// Operator
	float operator * (const Quaternion&) const;
	Quaternion operator * (float) const;
	Quaternion operator ^ (const Quaternion&) const;
    bool operator == (const Quaternion&) const;
    bool operator != (const Quaternion&) const;

	// Other
	friend class Vector3;
	friend class Vector4;
	friend class Matrix3x3;

};

}

#endif
