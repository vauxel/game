#include "vectors.h"

bool operator == (const Vector2& v1, const Vector2& v2) {
	return (v1.x == v2.x) && (v1.y == v2.y);
}

bool operator != (const Vector2& v1, const Vector2& v2) {
	return !(v1 == v2);
}

bool operator < (const Vector2& v1, const Vector2& v2) {
	return (v1.x < v2.x) && (v1.y < v2.y);
}

bool operator > (const Vector2& v1, const Vector2& v2) {
	return (v1.x > v2.x) && (v1.y > v2.y);
}

bool operator <= (const Vector2& v1, const Vector2& v2) {
	return (v1.x <= v2.x) && (v1.y <= v2.y);
}

bool operator >= (const Vector2& v1, const Vector2& v2) {
	return (v1.x >= v2.x) && (v1.y >= v2.y);
}

Vector2 operator + (Vector2& v1, const Vector2& v2) {
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2 operator + (Vector2& v1, const double f1) {
	return Vector2(v1.x + f1, v1.y + f1);
}

Vector2 operator - (Vector2& v1, const Vector2& v2) {
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}

Vector2 operator - (Vector2& v1, const double f1) {
	return Vector2(v1.x - f1, v1.y - f1);
}

Vector2& operator += (Vector2& v1, const Vector2& v2) {
	v1.x += v2.x; v1.y += v2.y;
	return v1;
}

Vector2& operator -= (Vector2& v1, const Vector2& v2) {
	v1.x -= v2.x; v1.y -= v2.y;
	return v1;
}

Vector2& operator += (Vector2& v1, const double f1) {
	v1.x += f1; v1.y += f1;
	return v1;
}

Vector2& operator -= (Vector2& v1, const double f1) {
	v1.x -= f1; v1.y -= f1;
	return v1;
}

Vector2 operator * (Vector2& v1, const double f1) {
	return Vector2(v1.x * f1, v1.y * f1);
}

Vector2& operator *= (Vector2& v1, const double f1) {
	v1.x *= f1; v1.y *= f1;
	return v1;
}

Vector2 operator / (Vector2& v1, const double f1) {
	return Vector2(v1.x / f1, v1.y / f1);
}

Vector2& operator /= (Vector2& v1, const double f1) {
	v1.x /= f1; v1.y /= f1;
	return v1;
}

double Vector2::dot(const Vector2& v1) {
	return (x * v1.x) + (y * v1.y);
}

double Vector2::magnitude() {
	return sqrt(x * x + y * y);
}

void Vector2::normalize() {
	*this /= magnitude();
}

bool operator == (const Vector3& v1, const Vector3& v2) {
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}

bool operator != (const Vector3& v1, const Vector3& v2) {
	return !(v1 == v2);
}

bool operator < (const Vector3& v1, const Vector3& v2) {
	return (v1.x < v2.x) && (v1.y < v2.y) && (v1.z < v2.z);
}

bool operator > (const Vector3& v1, const Vector3& v2) {
	return (v1.x > v2.x) && (v1.y > v2.y) && (v1.z > v2.z);
}

bool operator <= (const Vector3& v1, const Vector3& v2) {
	return (v1.x <= v2.x) && (v1.y <= v2.y) && (v1.z <= v2.z);
}

bool operator >= (const Vector3& v1, const Vector3& v2) {
	return (v1.x >= v2.x) && (v1.y >= v2.y) && (v1.z >= v2.z);
}

Vector3 operator + (Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator + (Vector3& v1, const double f1) {
	return Vector3(v1.x + f1, v1.y + f1, v1.z + f1);
}

Vector3 operator - (Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 operator - (Vector3& v1, const double f1) {
	return Vector3(v1.x - f1, v1.y - f1, v1.z - f1);
}

Vector3& operator += (Vector3& v1, const Vector3& v2) {
	v1.x += v2.x; v1.y += v2.y; v1.z += v2.z;
	return v1;
}

Vector3& operator -= (Vector3& v1, const Vector3& v2) {
	v1.x -= v2.x; v1.y -= v2.y; v1.z -= v2.z;
	return v1;
}

Vector3& operator += (Vector3& v1, const double f1) {
	v1.x += f1; v1.y += f1; v1.z += f1;
	return v1;
}

Vector3& operator -= (Vector3& v1, const double f1) {
	v1.x -= f1; v1.y -= f1; v1.z -= f1;
	return v1;
}

Vector3 operator * (Vector3& v1, const double f1) {
	return Vector3(v1.x * f1, v1.y * f1, v1.z * f1);
}

Vector3& operator *= (Vector3& v1, const double f1) {
	v1.x *= f1; v1.y *= f1; v1.z *= f1;
	return v1;
}

Vector3 operator / (Vector3& v1, const double f1) {
	return Vector3(v1.x / f1, v1.y / f1, v1.z / f1);
}

Vector3& operator /= (Vector3& v1, const double f1) {
	v1.x /= f1; v1.y /= f1; v1.z /= f1;
	return v1;
}

double Vector3::dot(const Vector3& v1) {
	return (x * v1.x) + (y * v1.y) + (z * v1.z);
}

Vector3 Vector3::cross(const Vector3& v1) {
	return Vector3(y * v1.z - z * v1.y, z * v1.x - x * v1.z, x * v1.y - y * v1.x);
}

double Vector3::magnitude() {
	return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize() {
	*this /= magnitude();
}