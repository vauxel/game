#include "vectors.h"

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

Vector3 operator + (Vector3& v1, const float f1) {
	return Vector3(v1.x + f1, v1.y + f1, v1.z + f1);
}

Vector3 operator - (Vector3& v1, const Vector3& v2) {
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 operator - (Vector3& v1, const float f1) {
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

Vector3& operator += (Vector3& v1, const float f1) {
	v1.x += f1; v1.y += f1; v1.z += f1;
	return v1;
}

Vector3& operator -= (Vector3& v1, const float f1) {
	v1.x -= f1; v1.y -= f1; v1.z -= f1;
	return v1;
}

Vector3 operator * (Vector3& v1, const float f1) {
	return Vector3(v1.x * f1, v1.y * f1, v1.z * f1);
}

Vector3& operator *= (Vector3& v1, const float f1) {
	v1.x *= f1; v1.y *= f1; v1.z *= f1;
	return v1;
}

Vector3 operator / (Vector3& v1, const float f1) {
	return Vector3(v1.x / f1, v1.y / f1, v1.z / f1);
}

Vector3& operator /= (Vector3& v1, const float f1) {
	v1.x /= f1; v1.y /= f1; v1.z /= f1;
	return v1;
}