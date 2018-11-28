#ifndef _MATRICES_H_
#define _MATRICES_H_

#include <math.h>
#include <assert.h>
#include "vectors.h"

typedef struct Matrix {
	double* _val;
	unsigned int size;

	Matrix(const unsigned int mSize);
	Matrix(const unsigned int mSize, double* values);
	Matrix() : Matrix(4) {};
	~Matrix();

	double& operator () (int x, int y);

	bool operator == (const Matrix&);
	bool operator != (const Matrix&);
	bool operator < (const Matrix&);
	bool operator > (const Matrix&);
	bool operator <= (const Matrix&);
	bool operator >= (const Matrix&);

	Matrix operator + (const Matrix&);
	Matrix operator - (const Matrix&);
	Matrix& operator += (const Matrix&);
	Matrix& operator -= (const Matrix&);

	Matrix operator * (const Matrix&);
	Matrix operator * (const double);
	Vector2 operator * (const Vector2&);
	Vector3 operator * (const Vector3&);
	Vector4 operator * (const Vector4&);

	Matrix& operator *= (const double);

	static Matrix identity();
	static Matrix translate(double x, double y, double z);
	static Matrix scale(double x, double y, double z);
} Matrix;

#endif