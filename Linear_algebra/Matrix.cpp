#include "Matrix.h"
#include <iostream>
#include <math.h>

Matrix::Matrix()
{
	_row = 2;
	_column = 2;
	c = new float[4];
	c[0] = 1;
	c[1] = 0;
	c[2] = 0;
	c[3] = 1;
}

Matrix::Matrix(char column, char row)
{
	_column = column;
	_row = row;
	c = new float[column * row];
	
	for(int i = 0, il = column; i < il; i++)
	{
		for(int j = 0, jl = row; j < jl; j++)
		{
			int value = static_cast<int>(i == j);
			c[column * i + j] = value;
		}
	}
}

Matrix::Matrix(float c1, float c2, float c3, float c4)
{
	_row = 2;
	_column = 2;
	c = new float[4];
	c[0] = c1;
	c[1] = c2;
	c[2] = c3;
	c[3] = c4;
}

Matrix::Matrix(float c1, float c2, float c3, float c4, float c5, float c6, float c7, float c8, float c9)
{
	_row = 3;
	_column = 3;
	c = new float[9];
	c[0] = c1;
	c[1] = c2;
	c[2] = c3;
	c[3] = c4;
	c[4] = c5;
	c[5] = c6;
	c[6] = c7;
	c[7] = c8;
	c[8] = c9;
}

Matrix::~Matrix()
{
	delete[] c;
}

Matrix::Matrix(const Matrix& obj)
{
	_column = obj._column;
	_row = obj._row;

	const int length = _column * _row;
	c = new float[length];
	
	for(int i = 0; i < length; i++)
		c[i] = obj.c[i];
}

Matrix Matrix::identity()
{
	return Matrix(
		1, 0,
		0, 1
	);
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
	const int size = a.getSize();
	
	if (size == b.getSize())
		return Matrix();

	Matrix result;
	for (int i = 0; i < size; i++)
		result.c[i] = a.c[i] + b.c[i];

	return result;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	const int size = a.getSize();

	if (size == b.getSize())
		return Matrix();

	Matrix result;
	for (int i = 0; i < size; i++)
		result.c[i] = a.c[i] - b.c[i];

	return result;
}

Matrix operator*(const Matrix& a, const float b)
{
	Matrix result;
	for (auto i = 0, il = a.getSize(); i < il; i++)
		result.c[i] = a.c[i] * b;

	return result;
}

Matrix operator*(const float a, const Matrix& b)
{
	Matrix result;
	for (auto i = 0, il = b.getSize(); i < il; i++)
		result.c[i] = b.c[i] * a;

	return result;
}

Vector2D operator*(const Matrix& a, const Vector2D& b)
{
	if (a._row != 3 || a._column != 3)
		return b;

	return Vector2D(
		(a.c[0] * b.x) + (a.c[1] * b.y) + (a.c[2] * b.w),
		(a.c[3] * b.x) + (a.c[4] * b.y) + (a.c[5] * b.w));
}

Vector2D operator*(const Vector2D& a, const Matrix& b)
{
	if (b._row != 3 || b._column != 3)
		return a;

	return Vector2D(
		(b.c[0] * a.x) + (b.c[1] * a.y) + (b.c[2] * a.w),
		(b.c[3] * a.x) + (b.c[4] * a.y) + (b.c[5] * a.w));
}

Vector3D operator*(const Matrix& a, const Vector3D& b)
{
	if (a._row != 4 || a._column != 4)
		return b;

	return Vector3D(
		(a.c[0] * b.x) + (a.c[1] * b.y) + (a.c[2] * b.z) + (a.c[3] * b.w),
		(a.c[4] * b.x) + (a.c[5] * b.y) + (a.c[6] * b.z) + (a.c[7] * b.w),
		1 //(a.c[8] * b.x) + (a.c[9] * b.y) + (a.c[10] * b.z) + (a.c[11] * b.w)
	);
}

Vector3D operator*(const Vector3D& a, const Matrix& b)
{
	if (b._row != 4 || b._column != 4)
		return a;

	return Vector3D(
		(b.c[0] * a.x) + (b.c[1] * a.y) + (b.c[2] * a.z) + (b.c[3] * a.w),
		(b.c[4] * a.x) + (b.c[5] * a.y) + (b.c[6] * a.z) + (b.c[7] * a.w),
		1 //(b.c[8] * a.x) + (b.c[9] * a.y) + (b.c[10] * a.z) + (b.c[11] * a.w)
	);
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
	if (a._row != b._row || a._column != b._column)
		return a;

	Matrix matrix(a._row, a._column);

	for (int i = 0, il = a._row; i < il; ++i)
	{
		for (int j = 0, jl = a._column; j < jl; ++j)
		{
			float sum = 0.0f;
			int index = j * a._column + i;

			for (int k = 0, kl = a._column; k < kl; ++k)
			{
				int ik = k * a._column + i;
				int kj = j * a._column + k;
				sum += a.c[ik] * b.c[kj];
			}
						
			matrix.c[index] = sum;
		}
	}

	return matrix;
}

std::ostream& operator<<(std::ostream& outstream, const Matrix& matrix)
{
	outstream << "Matrix" << matrix._column << "x" << matrix._row << " -";
	
	for(int i = 0, il = matrix._column * matrix._row; i < il; i++)
	{ 
		outstream << " c" << i << ": " << matrix.c[i] << ",";
	}
	return outstream;
}

int Matrix::getSize() const
{
	return _row * _column;
}

Matrix Matrix::scale(const float a)
{
	Matrix matrix = Matrix(_column, _row);
	
	for(auto i = 0, il = _row * _column - 1; i < il; i += _column + 1)
		matrix.c[i] = c[i] * a;

	return (*this) * matrix;
}

Matrix Matrix::scale(float a, float b) const
{
	if (_row < 3 || _column < 3)
		return (*this);

	Matrix matrix = Matrix(_column, _row);

	unsigned char index = 0;
	matrix.c[index] = c[index] * a;

	index = _column + 1;
	matrix.c[index] = c[index] * b;

	return (*this) * matrix;
}

Matrix Matrix::scale(const Vector2D& scale) const
{
	if (_row < 3 || _column < 3)
		return (*this);

	Matrix matrix = Matrix(_column, _row);

	unsigned char index = 0;
	matrix.c[index] *= scale.x;

	index = _column + 1;
	matrix.c[index] *= scale.y;

	return (*this) * matrix;
}

Matrix Matrix::scale(float x, float y, float z) const
{
	if (_row < 4 || _column < 4)
		return (*this);

	Matrix matrix = Matrix(_column, _row);

	unsigned char index = 0;
	matrix.c[index] = c[index] * x;

	index = _column + 1;
	matrix.c[index] = c[index] * y;

	index += _column + 1;
	matrix.c[index] = c[index] * z;

	return (*this) * matrix;
}

Matrix Matrix::rotate(float radians)
{
	if (_row != 3 || _column != 3)
		return (*this);

	Matrix matrix = Matrix(_column, _row);
	matrix.c[0] *= cos(radians);
	matrix.c[1] = -sin(radians);
	matrix.c[3] = sin(radians);
	matrix.c[4] *= cos(radians);
	return (*this) * matrix;

//	std::cout << matrix << std::endl;

//	for (int i = 0, il = _column - 1; i < il; ++i)
//	{ 
//		for(int j = 0, jl = _row - 1; j < jl; ++j)
//		{
//			unsigned int index = _column * j + i;
//
//			if (index % 2 == 0)
//				matrix.c[index] = sin(radians);
//			else
//				matrix.c[index] = cos(radians);
//		}
//	}

//	std::cout << matrix << std::endl;

}

Matrix Matrix::rotate(const Vector2D& forward, const Vector2D& side) const
{
	if (_row != 3 || _column != 3)
		return (*this);

	//todo: RECENTLY UPDATED, NOT 100% SURE IF CORRECT
	Matrix matrix = Matrix(_column, _row);
	matrix.c[0] = forward.x;
	matrix.c[3] = forward.y;
	matrix.c[1] = side.x;
	matrix.c[4] = side.y;

	return (*this) * matrix;
}

Matrix Matrix::rotateX(float x) const
{
	if (_row != 4 || _column != 4)
		return (*this);

	Matrix matrix = Matrix(_column, _row);
	matrix.c[5] = cos(x);
	matrix.c[6] = -sin(x);
	matrix.c[9] = sin(x);
	matrix.c[10] = cos(x);
	return (*this) * matrix;
}

Matrix Matrix::rotateY(float y) const
{
	if (_row != 4 || _column != 4)
		return (*this);

	Matrix matrix = Matrix(_column, _row);
	matrix.c[0] = cos(y);
	matrix.c[2] = sin(y);
	matrix.c[8] = -sin(y);
	matrix.c[10] = cos(y);
	return (*this) * matrix;
}

Matrix Matrix::rotateZ(float z) const
{
	if (_row != 4 || _column != 4)
		return (*this);

	Matrix matrix = Matrix(_column, _row);
	matrix.c[0] = cos(z);
	matrix.c[1] = -sin(z);
	matrix.c[4] = sin(z);
	matrix.c[5] = cos(z);
	return (*this) * matrix;
}

Matrix Matrix::translate(float x, float y)
{
	if (_row < 3 || _column < 3)
		return (*this);

	Matrix matrix = Matrix(_column, _row);
	matrix.c[_column - 1]		+= x;
	matrix.c[_column * 2 - 1]	+= y;
	return (*this) * matrix;
}

Matrix Matrix::translate(const Vector2D& translation) const
{
	if (_row < 3 || _column < 3)
		return (*this);

	Matrix matrix = Matrix(_column, _row);
	matrix.c[_column - 1] += translation.x;
	matrix.c[_column * 2 - 1] += translation.y;
	return (*this) * matrix;
}

Matrix Matrix::translate(float x, float y, float z)
{
	if (_row < 4 || _column < 4)
		return (*this);

	Matrix matrix = Matrix(_column, _row);
	matrix.c[_column - 1] += x;
	matrix.c[_column * 2 - 1] += y;
	matrix.c[_column * 3 - 1] += z;
	return (*this) * matrix;
}

Matrix Matrix::lookAt(const Vector3D& eye, const Vector3D& target, const Vector3D& up)
{
	Vector3D f = Vector3D::normalize(target - eye);
	Vector3D u = Vector3D::normalize(up);
	Vector3D s = Vector3D::normalize(Vector3D::crossProduct(f, u));
	u = Vector3D::crossProduct(s, f);

	Matrix result = Matrix(4, 4);
	result.c[0] = s.x;
	result.c[1] = s.y;
	result.c[2] = s.z;
	result.c[4] = u.x;
	result.c[5] = u.y;
	result.c[6] = u.z;
	result.c[8] = -f.x;
	result.c[9] = -f.y;
	result.c[10] = -f.z;
	result.c[3] = -Vector3D::dotProduct(s, eye);
	result.c[7] = -Vector3D::dotProduct(u, eye);
	result.c[11] = Vector3D::dotProduct(f, eye);
	return result;
}

Matrix Matrix::view(float xRotation, float yRotation, float magnitude)
{
	if (_row != 4 || _column != 4)
		return (*this);

	//YRotation = O with horizontal dash
	//XRotation = O with vertical dash

	Matrix matrix = (*this);
	matrix.c[0] = -sin(yRotation);
	matrix.c[1] = cos(yRotation);
	matrix.c[4] = -cos(yRotation) * cos(xRotation);
	matrix.c[5] = -cos(xRotation) * sin(yRotation);
	matrix.c[6] = sin(xRotation);
	matrix.c[8] = cos(yRotation) * sin(xRotation);
	matrix.c[9] = sin(yRotation) * sin(xRotation);
	matrix.c[10] = cos(xRotation);
	matrix.c[11] = -magnitude;
	return matrix;
}
