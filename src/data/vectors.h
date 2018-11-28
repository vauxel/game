#ifndef _VECTORS_H_
#define _VECTORS_H_

#include <math.h>

typedef struct Vector2 {
	double x, y;

	Vector2(double x, double y) : x(x), y(y) {};
	Vector2() : x(0.0), y(0.0) {};

	bool operator == (const Vector2&);
	bool operator != (const Vector2&);
	bool operator < (const Vector2&);
	bool operator > (const Vector2&);
	bool operator <= (const Vector2&);
	bool operator >= (const Vector2&);

	Vector2 operator + (const Vector2&);
	Vector2 operator + (const double);
	
	Vector2 operator - (const Vector2&);
	Vector2 operator - (const double);

	Vector2& operator += (const Vector2&);
	Vector2& operator += (const double);

	Vector2& operator -= (const Vector2&);
	Vector2& operator -= (const double);

	Vector2 operator * (const double);
	Vector2& operator *= (const double);

	Vector2 operator / (const double);
	Vector2& operator /= (const double);

	double dot(const Vector2& v1);
	double magnitude();
	void normalize();
} Vector2;

typedef struct Vector3 {
	double x, y, z;

	Vector3(double x, double y, double z) : x(x), y(y), z(z) {};
	Vector3() : x(0.0), y(0.0), z(0.0) {};

	bool operator == (const Vector3&);
	bool operator != (const Vector3&);
	bool operator < (const Vector3&);
	bool operator > (const Vector3&);
	bool operator <= (const Vector3&);
	bool operator >= (const Vector3&);

	Vector3 operator + (const Vector3&);
	Vector3 operator + (const double);
	
	Vector3 operator - (const Vector3&);
	Vector3 operator - (const double);

	Vector3& operator += (const Vector3&);
	Vector3& operator += (const double);

	Vector3& operator -= (const Vector3&);
	Vector3& operator -= (const double);

	Vector3 operator * (const double);
	Vector3& operator *= (const double);

	Vector3 operator / (const double);
	Vector3& operator /= (const double);

	double dot(const Vector3& v1);
	Vector3 cross(const Vector3& v1);
	double magnitude();
	void normalize();
} Vector3;

typedef struct Vector4 {
	double x, y, z, w;

	Vector4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {};
	Vector4() : x(0.0), y(0.0), z(0.0), w(0.0) {};

	bool operator == (const Vector4&);
	bool operator != (const Vector4&);
	bool operator < (const Vector4&);
	bool operator > (const Vector4&);
	bool operator <= (const Vector4&);
	bool operator >= (const Vector4&);

	Vector4 operator + (const Vector4&);
	Vector4 operator + (const double);
	
	Vector4 operator - (const Vector4&);
	Vector4 operator - (const double);

	Vector4& operator += (const Vector4&);
	Vector4& operator += (const double);

	Vector4& operator -= (const Vector4&);
	Vector4& operator -= (const double);

	Vector4 operator * (const double);
	Vector4& operator *= (const double);

	Vector4 operator / (const double);
	Vector4& operator /= (const double);

	double dot(const Vector4& v1);
	double magnitude();
	void normalize();
} Vector4;

#endif