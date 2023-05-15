#ifndef __MT_VECTOR_2_INT_H__
#define __MT_VECTOR_2_INT_H__

namespace mt {

class Vector2i
{
public:

	// Variables
	int x, y;

	// Forwards
	Vector2i();
	Vector2i(int x, int y);
	Vector2i(const Vector2i &v);
	~Vector2i();

	// Natives
	float squareLength() const;
	float length() const;
	void set(int x, int y);
	void set(const Vector2i &v);
	
	// Operator
    int operator [] (unsigned int index) const;
    int& operator [] (unsigned int index);
    bool operator == (const Vector2i& v) const;
    bool operator != (const Vector2i& v) const;
	Vector2i& operator = (const Vector2i &v);

};

}

#endif
