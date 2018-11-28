#include "quaternion.h"

Quaternion::Quaternion(double roll, double pitch, double yaw) {
	double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
	double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
	double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
	
    this->w = cy * cr * cp + sy * sr * sp;
    this->x = cy * sr * cp - sy * cr * sp;
    this->y = cy * cr * sp + sy * sr * cp;
    this->z = sy * cr * cp - cy * sr * sp;
}

Matrix Quaternion::matrix4() {
	Matrix mat = Matrix(3);

	double tx = this->x + this->x;
	double ty = this->y + this->y;
	double tz = this->z + this->z;

	double twx = tx * w;
	double twy = ty * w;
	double twz = tz * w;
	double txx = tx * x;
	double txy = ty * x;
	double txz = tz * x;
	double tyy = ty * y;
	double tyz = tz * y;
	double tzz = tz * z;

	mat(0, 0) = 1.0 - (tyy + tzz);
	mat(0, 1) = txy - twz;
	mat(0, 2) = txz + twy;
	mat(1, 0) = txy + twz;
	mat(1, 1) = 1.0 - (txx + tzz);
	mat(1, 2) = tyz - twx;
	mat(2, 0) = txz - twy;
	mat(2, 1) = tyz + twx;
	mat(2, 2) = 1.0 - (txx + tyy);

	return mat;
}

Quaternion Quaternion::operator + (const Quaternion& q) {
	return Quaternion(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z);
}

Quaternion Quaternion::operator - (const Quaternion& q) {
	return Quaternion(this->w - q.w, this->x - q.x, this->y - q.y, this->z - q.z);
}

Quaternion Quaternion::operator * (const double s) {
	return Quaternion(this->w * s, this->x * s, this->y * s, this->z * s);
}