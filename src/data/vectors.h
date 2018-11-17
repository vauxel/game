#ifndef _VECTORS_H_
#define _VECTORS_H_

#include <math.h>

typedef struct Vector2 {
	double x;
	double y;

	Vector2(double x, double y) : x(x), y(y) {};
	Vector2() : x(0.0), y(0.0) {};

	friend bool operator == (const Vector2&, const Vector2&);
	friend bool operator != (const Vector2&, const Vector2&);
	friend bool operator < (const Vector2&, const Vector2&);
	friend bool operator > (const Vector2&, const Vector2&);
	friend bool operator <= (const Vector2&, const Vector2&);
	friend bool operator >= (const Vector2&, const Vector2&);

	friend Vector2 operator + (Vector2&, const Vector2&);
	friend Vector2 operator + (Vector2&, const double);
	
	friend Vector2 operator - (Vector2&, const Vector2&);
	friend Vector2 operator - (Vector2&, const double);

	friend Vector2& operator += (Vector2&, const Vector2&);
	friend Vector2& operator += (Vector2&, const double);

	friend Vector2& operator -= (Vector2&, const Vector2&);
	friend Vector2& operator -= (Vector2&, const double);

	friend Vector2 operator * (Vector2&, const double);
	friend Vector2& operator *= (Vector2&, const double);

	friend Vector2 operator / (Vector2&, const double);
	friend Vector2& operator /= (Vector2&, const double);

	double dot(const Vector2& v1);
	double magnitude();
	void normalize();
} Vector2;

typedef struct Vector3 {
	double x;
	double y;
	double z;

	Vector3(double x, double y, double z) : x(x), y(y), z(z) {};
	Vector3() : x(0.0), y(0.0), z(0.0) {};

	friend bool operator == (const Vector3&, const Vector3&);
	friend bool operator != (const Vector3&, const Vector3&);
	friend bool operator < (const Vector3&, const Vector3&);
	friend bool operator > (const Vector3&, const Vector3&);
	friend bool operator <= (const Vector3&, const Vector3&);
	friend bool operator >= (const Vector3&, const Vector3&);

	friend Vector3 operator + (Vector3&, const Vector3&);
	friend Vector3 operator + (Vector3&, const double);
	
	friend Vector3 operator - (Vector3&, const Vector3&);
	friend Vector3 operator - (Vector3&, const double);

	friend Vector3& operator += (Vector3&, const Vector3&);
	friend Vector3& operator += (Vector3&, const double);

	friend Vector3& operator -= (Vector3&, const Vector3&);
	friend Vector3& operator -= (Vector3&, const double);

	friend Vector3 operator * (Vector3&, const double);
	friend Vector3& operator *= (Vector3&, const double);

	friend Vector3 operator / (Vector3&, const double);
	friend Vector3& operator /= (Vector3&, const double);

	double dot(const Vector3& v1);
	Vector3 cross(const Vector3& v1);
	double magnitude();
	void normalize();
} Vector3;

#endif