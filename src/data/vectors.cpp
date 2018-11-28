#include "vectors.h"

bool Vector2::operator == (const Vector2& v2) {
	return (this->x == v2.x) && (this->y == v2.y);
}

bool Vector2::operator != (const Vector2& v2) {
	return !(*this == v2);
}

bool Vector2::operator < (const Vector2& v2) {
	return (this->x < v2.x) && (this->y < v2.y);
}

bool Vector2::operator > (const Vector2& v2) {
	return (this->x > v2.x) && (this->y > v2.y);
}

bool Vector2::operator <= (const Vector2& v2) {
	return (this->x <= v2.x) && (this->y <= v2.y);
}

bool Vector2::operator >= (const Vector2& v2) {
	return (this->x >= v2.x) && (this->y >= v2.y);
}

Vector2 Vector2::operator + (const Vector2& v2) {
	return Vector2(this->x + v2.x, this->y + v2.y);
}

Vector2 Vector2::operator + (const double f1) {
	return Vector2(this->x + f1, this->y + f1);
}

Vector2 Vector2::operator - (const Vector2& v2) {
	return Vector2(this->x - v2.x, this->y - v2.y);
}

Vector2 Vector2::operator - (const double f1) {
	return Vector2(this->x - f1, this->y - f1);
}

Vector2& Vector2::operator += (const Vector2& v2) {
	this->x += v2.x; this->y += v2.y;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& v2) {
	this->x -= v2.x; this->y -= v2.y;
	return *this;
}

Vector2& Vector2::operator += (const double f1) {
	this->x += f1; this->y += f1;
	return *this;
}

Vector2& Vector2::operator -= (const double f1) {
	this->x -= f1; this->y -= f1;
	return *this;
}

Vector2 Vector2::operator * (const double f1) {
	return Vector2(this->x * f1, this->y * f1);
}

Vector2& Vector2::operator *= (const double f1) {
	this->x *= f1; this->y *= f1;
	return *this;
}

Vector2 Vector2::operator / (const double f1) {
	return Vector2(this->x / f1, this->y / f1);
}

Vector2& Vector2::operator /= (const double f1) {
	this->x /= f1; this->y /= f1;
	return *this;
}

double Vector2::dot(const Vector2& v2) {
	return (this->x * v2.x) + (this->y * v2.y);
}

double Vector2::magnitude() {
	return sqrt(this->x * this->x + this->y * this->y);
}

void Vector2::normalize() {
	*this /= magnitude();
}

bool Vector3::operator == (const Vector3& v2) {
	return (this->x == v2.x) && (this->y == v2.y) && (this->z == v2.z);
}

bool Vector3::operator != (const Vector3& v2) {
	return !(*this == v2);
}

bool Vector3::operator < (const Vector3& v2) {
	return (this->x < v2.x) && (this->y < v2.y) && (this->z < v2.z);
}

bool Vector3::operator > (const Vector3& v2) {
	return (this->x > v2.x) && (this->y > v2.y) && (this->z > v2.z);
}

bool Vector3::operator <= (const Vector3& v2) {
	return (this->x <= v2.x) && (this->y <= v2.y) && (this->z <= v2.z);
}

bool Vector3::operator >= (const Vector3& v2) {
	return (this->x >= v2.x) && (this->y >= v2.y) && (this->z >= v2.z);
}

Vector3 Vector3::operator + (const Vector3& v2) {
	return Vector3(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

Vector3 Vector3::operator + (const double f1) {
	return Vector3(this->x + f1, this->y + f1, this->z + f1);
}

Vector3 Vector3::operator - (const Vector3& v2) {
	return Vector3(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

Vector3 Vector3::operator - (const double f1) {
	return Vector3(this->x - f1, this->y - f1, this->z - f1);
}

Vector3& Vector3::operator += (const Vector3& v2) {
	this->x += v2.x; this->y += v2.y; this->z += v2.z;
	return *this;
}

Vector3& Vector3::operator -= (const Vector3& v2) {
	this->x -= v2.x; this->y -= v2.y; this->z -= v2.z;
	return *this;
}

Vector3& Vector3::operator += (const double f1) {
	this->x += f1; this->y += f1; this->z += f1;
	return *this;
}

Vector3& Vector3::operator -= (const double f1) {
	this->x -= f1; this->y -= f1; this->z -= f1;
	return *this;
}

Vector3 Vector3::operator * (const double f1) {
	return Vector3(this->x * f1, this->y * f1, this->z * f1);
}

Vector3& Vector3::operator *= (const double f1) {
	this->x *= f1; this->y *= f1; this->z *= f1;
	return *this;
}

Vector3 Vector3::operator / (const double f1) {
	return Vector3(this->x / f1, this->y / f1, this->z / f1);
}

Vector3& Vector3::operator /= (const double f1) {
	this->x /= f1; this->y /= f1; this->z /= f1;
	return *this;
}

double Vector3::dot(const Vector3& v2) {
	return (this->x * v2.x) + (this->y * v2.y) + (this->z * v2.z);
}

Vector3 Vector3::cross(const Vector3& v2) {
	return Vector3(this->y * v2.z - this->z * v2.y, this->z * v2.x - this->x * v2.z, this->x * v2.y - this->y * v2.x);
}

double Vector3::magnitude() {
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vector3::normalize() {
	*this /= magnitude();
}



bool Vector4::operator == (const Vector4& v2) {
	return (this->x == v2.x) && (this->y == v2.y) && (this->z == v2.z) && (this->w == v2.w);
}

bool Vector4::operator != (const Vector4& v2) {
	return !(*this == v2);
}

bool Vector4::operator < (const Vector4& v2) {
	return (this->x < v2.x) && (this->y < v2.y) && (this->z < v2.z) && (this->w < v2.w);
}

bool Vector4::operator > (const Vector4& v2) {
	return (this->x > v2.x) && (this->y > v2.y) && (this->z > v2.z) && (this->w > v2.w);
}

bool Vector4::operator <= (const Vector4& v2) {
	return (this->x <= v2.x) && (this->y <= v2.y) && (this->z <= v2.z) && (this->w <= v2.w);
}

bool Vector4::operator >= (const Vector4& v2) {
	return (this->x >= v2.x) && (this->y >= v2.y) && (this->z >= v2.z) && (this->w >= v2.w);
}

Vector4 Vector4::operator + (const Vector4& v2) {
	return Vector4(this->x + v2.x, this->y + v2.y, this->z + v2.z, this->w + v2.w);
}

Vector4 Vector4::operator + (const double f1) {
	return Vector4(this->x + f1, this->y + f1, this->z + f1, this->w + f1);
}

Vector4 Vector4::operator - (const Vector4& v2) {
	return Vector4(this->x - v2.x, this->y - v2.y, this->z - v2.z, this->w - v2.w);
}

Vector4 Vector4::operator - (const double f1) {
	return Vector4(this->x - f1, this->y - f1, this->z - f1, this->w - f1);
}

Vector4& Vector4::operator += (const Vector4& v2) {
	this->x += v2.x; this->y += v2.y; this->z += v2.z; this->w += v2.w;
	return *this;
}

Vector4& Vector4::operator -= (const Vector4& v2) {
	this->x -= v2.x; this->y -= v2.y; this->z -= v2.z; this->w -= v2.w;
	return *this;
}

Vector4& Vector4::operator += (const double f1) {
	this->x += f1; this->y += f1; this->z += f1; this->w += f1;
	return *this;
}

Vector4& Vector4::operator -= (const double f1) {
	this->x -= f1; this->y -= f1; this->z -= f1; this->w -= f1;
	return *this;
}

Vector4 Vector4::operator * (const double f1) {
	return Vector4(this->x * f1, this->y * f1, this->z * f1, this->w * f1);
}

Vector4& Vector4::operator *= (const double f1) {
	this->x *= f1; this->y *= f1; this->z *= f1; this->w *= f1;
	return *this;
}

Vector4 Vector4::operator / (const double f1) {
	return Vector4(this->x / f1, this->y / f1, this->z / f1, this->w / f1);
}

Vector4& Vector4::operator /= (const double f1) {
	this->x /= f1; this->y /= f1; this->z /= f1; this->w /= f1;
	return *this;
}

double Vector4::dot(const Vector4& v2) {
	return (this->x * v2.x) + (this->y * v2.y) + (this->z * v2.z) + (this->w * v2.w);
}

double Vector4::magnitude() {
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

void Vector4::normalize() {
	*this /= magnitude();
}