#ifndef MATRIX_H
#define MATRIX_H

#include "Vector3D.h"
#include "Vector2D.h"

class Matrix
{
private:
	char _column;
	char _row;

	float* c;

public:
	Matrix();
	Matrix(char column, char row);
	Matrix(float c1, float c2, float c3, float c4);
	Matrix(float c1, float c2, float c3, float c4, float c5, float c6, float c7, float c8, float c9);
	~Matrix();
	Matrix(const Matrix &obj);
	Matrix identity();
	int getSize() const;
	friend Matrix operator+(const Matrix& a, const Matrix& b);
	friend Matrix operator-(const Matrix& a, const Matrix& b);
	friend Matrix operator*(const Matrix& a, const float b);
	friend Matrix operator*(const float a, const Matrix& b);
	friend Vector2D operator*(const Matrix& a, const Vector2D& b);
	friend Vector2D operator*(const Vector2D& a, const Matrix& b);
	friend Vector3D operator*(const Matrix& a, const Vector3D& b);
	friend Vector3D operator*(const Vector3D& a, const Matrix& b);
	friend Matrix operator*(const Matrix& a, const Matrix& b);
	friend std::ostream& operator<<(std::ostream& outstream, const Matrix& matrix);
	Matrix scale(float a);
	Matrix scale(float a, float b) const;
	Matrix scale(const Vector2D& scale) const;
	Matrix scale(float x, float y, float z) const;
	Matrix rotate(float radians);
	Matrix rotate(const Vector2D& forward, const Vector2D& side) const;
	Matrix rotateX(float x) const;
	Matrix rotateY(float y) const;
	Matrix rotateZ(float z) const;
	Matrix translate(float x, float y);
	Matrix translate(const Vector2D& translation) const;
	Matrix translate(float x, float y, float z);
	Matrix lookAt(const Vector3D& eye, const Vector3D& target, const Vector3D& up);
	Matrix view(float yRotation, float xRotation, float magnitude);
};

#endif

