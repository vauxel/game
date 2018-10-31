#ifndef _VECTORS_H_
#define _VECTORS_H_

typedef struct Vector3 {
	double x;
	double y;
	double z;

	Vector3(double x, double y, double z) : x(x), y(y), z(z) {};
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {};

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