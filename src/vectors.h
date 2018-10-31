#ifndef _VECTORS_H_
#define _VECTORS_H_

typedef struct Vector3 {
	float x;
	float y;
	float z;

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {};

	friend bool operator == (const Vector3&, const Vector3&);
	friend bool operator != (const Vector3&, const Vector3&);
	friend bool operator < (const Vector3&, const Vector3&);
	friend bool operator > (const Vector3&, const Vector3&);
	friend bool operator <= (const Vector3&, const Vector3&);
	friend bool operator >= (const Vector3&, const Vector3&);

	friend Vector3 operator + (Vector3&, const Vector3&);
	friend Vector3 operator + (Vector3&, const float);
	
	friend Vector3 operator - (Vector3&, const Vector3&);
	friend Vector3 operator - (Vector3&, const float);

	friend Vector3& operator += (Vector3&, const Vector3&);
	friend Vector3& operator += (Vector3&, const float);

	friend Vector3& operator -= (Vector3&, const Vector3&);
	friend Vector3& operator -= (Vector3&, const float);

	friend Vector3 operator * (Vector3&, const float);
	friend Vector3& operator *= (Vector3&, const float);

	friend Vector3 operator / (Vector3&, const float);
	friend Vector3& operator /= (Vector3&, const float);
} Vector3;

#endif