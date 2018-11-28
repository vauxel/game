#include "matrices.h"
#include "vectors.h"

Matrix::Matrix(const unsigned int mSize) {
	size = mSize;
	_val = new double[mSize * mSize];
}

Matrix::Matrix(const unsigned int mSize, double* values) {
	size = mSize;
	_val = new double[mSize * mSize];

	for(unsigned int i = 0; i < (mSize * mSize); i++) {
		_val[i] = values[i];
	}
}

Matrix::~Matrix() {
	delete[] _val;
}

double& Matrix::operator () (int x, int y) {
	return this->_val[x + this->size * y];
}

bool Matrix::operator == (const Matrix& m) {
	assert(this->size == m.size);

	for(unsigned int i = 0; i < (this->size * this->size); i++) {
		if(this->_val[i] != m._val[i]) {
			return false;
		}
	}

	return true;
}

bool Matrix::operator != (const Matrix& m) {
	return !(*this == m);
}

bool Matrix::operator < (const Matrix& m) {
	assert(this->size == m.size);

	for(unsigned int i = 0; i < (this->size * this->size); i++) {
		if(this->_val[i] < m._val[i]) {
			return false;
		}
	}

	return true;
}

bool Matrix::operator > (const Matrix& m) {
	assert(this->size == m.size);

	for(unsigned int i = 0; i < (this->size * this->size); i++) {
		if(this->_val[i] > m._val[i]) {
			return false;
		}
	}

	return true;
}

bool Matrix::operator <= (const Matrix& m) {
	assert(this->size == m.size);

	for(unsigned int i = 0; i < (this->size * this->size); i++) {
		if(this->_val[i] <= m._val[i]) {
			return false;
		}
	}

	return true;
}

bool Matrix::operator >= (const Matrix& m) {
	assert(this->size == m.size);

	for(unsigned int i = 0; i < (this->size * this->size); i++) {
		if(this->_val[i] >= m._val[i]) {
			return false;
		}
	}

	return true;
}

Matrix Matrix::operator + (const Matrix& m) {
	assert(this->size == m.size);
	Matrix m2 = Matrix(this->size);

	for(unsigned int i = 0; i < (m2.size * m2.size); i++) {
		m2._val[i] = this->_val[i] + m._val[i];
	}

	return m2;
}

Matrix& Matrix::operator += (const Matrix& m) {
	assert(this->size == m.size);

	for(unsigned int i = 0; i < (this->size * this->size); i++) {
		this->_val[i] += m._val[i];
	}

	return *this;
}

Matrix Matrix::operator - (const Matrix& m) {
	assert(this->size == m.size);
	Matrix m2 = Matrix(this->size);

	for(unsigned int i = 0; i < (m2.size * m2.size); i++) {
		m2._val[i] = this->_val[i] - m._val[i];
	}

	return m2;
}

Matrix& Matrix::operator -= (const Matrix& m) {
	assert(this->size == m.size);

	for(unsigned int i = 0; i < (this->size * this->size); i++) {
		this->_val[i] -= m._val[i];
	}

	return *this;
}

Matrix Matrix::operator * (const Matrix& m) {
	assert(this->size == m.size);
	Matrix m2 = Matrix(this->size);

	for(unsigned int y = 0; y < m2.size; y++) {
		for(unsigned int x = 0; x < m2.size; x++) {
			double sum = 0;

			for(unsigned int i = 0; i < m2.size; i++) {
				sum += this->_val[y * this->size + i] * m._val[i * m.size + x];
			}

			m2._val[x + m2.size * y] = sum;
		}
	}

	return m2;
}

Matrix Matrix::operator * (const double s) {
	Matrix m2 = Matrix(this->size);

	for(unsigned int i = 0; i < (this->size * this->size); i++) {
		this->_val[i] *= s;
	}

	return m2;
}

Vector2 Matrix::operator * (const Vector2& v) {
	assert(this->size == 2);
	Vector2 v2 = Vector2();

	for(unsigned int i = 0; i < this->size; i++) {
		v2.x += this->_val[i + this->size * 0] * v.x;
		v2.y += this->_val[i + this->size * 1] * v.y;
	}

	return v2;
}

Vector3 Matrix::operator * (const Vector3& v) {
	assert(this->size == 3);
	Vector3 v2 = Vector3();

	for(unsigned int i = 0; i < this->size; i++) {
		v2.x += this->_val[i + this->size * 0] * v.x;
		v2.y += this->_val[i + this->size * 1] * v.y;
		v2.z += this->_val[i + this->size * 2] * v.z;
	}

	return v2;
}

Vector4 Matrix::operator * (const Vector4& v) {
	assert(this->size == 4);
	Vector4 v2 = Vector4();

	for(unsigned int i = 0; i < this->size; i++) {
		v2.x += this->_val[i + this->size * 0] * v.x;
		v2.y += this->_val[i + this->size * 1] * v.y;
		v2.z += this->_val[i + this->size * 2] * v.z;
		v2.w += this->_val[i + this->size * 2] * v.w;
	}

	return v2;
}

Matrix& Matrix::operator *= (const double s) {
	for(unsigned int i = 0; i < (this->size * this->size); i++) {
		this->_val[i] *= s;
	}

	return *this;
}

Matrix Matrix::identity() {
	double values[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	return Matrix(4, values);
}

Matrix Matrix::translate(double x, double y, double z) {
	double values[16] = {1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1};
	return Matrix(4, values);
}

Matrix Matrix::scale(double x, double y, double z) {
	double values[16] = {x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1};
	return Matrix(4, values);
}