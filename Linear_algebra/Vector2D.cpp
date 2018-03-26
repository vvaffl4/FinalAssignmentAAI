#include "Vector2D.h"
#include <vector>
#include "Matrix.h"


Vector2D::Vector2D() :
	x(0.0f), y(0.0f), w(1.0f)
{}

Vector2D::Vector2D(float x, float y) :
	x(x), y(y), w(1.0f)
{}


Vector2D::~Vector2D()
{
}

void Vector2D::add(const Vector2D& other)
{
	this->x += other.x;
	this->y += other.y;
}

void Vector2D::add(const float x, const float y)
{
	this->x += x;
	this->y += y;
}

float Vector2D::magnitude() const
{
	return sqrt(x * x + y * y);
}

float Vector2D::magnitudeSqrt() const
{
	return (x * x + y * y);
}

float Vector2D::dotProduct(const Vector2D& other) const
{
	return (x * other.x + y * other.y);
}

void Vector2D::normalize()
{
	float magnitude = sqrt(x * x + y * y);

	x = x / magnitude;
	y = y / magnitude;
}

void Vector2D::clamp(float magnitude)
{
	float currentMagnitude = sqrt(x * x + y * y);

	if (currentMagnitude > magnitude)
	{
		normalize();
		x *= magnitude;
		y *= magnitude;
	}
}

Vector2D Vector2D::perpendicular(const Vector2D& vector)
{
	return Vector2D(-vector.y, vector.x);
}

Vector2D Vector2D::rotateAroundOrigin(const Vector2D& vector, float rotation)
{
	return (Matrix(3, 3)
		.rotate(rotation) * vector);
}

std::string Vector2D::toString() const
{
	std::stringstream input;
	input << "Vector2 - x: " << x << ", y:" << y << ";";
	return input.str();
}

Vector2D operator+(const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.x + b.x, a.y + b.y);
}

Vector2D operator+(const Vector2D& a, float b)
{
	return Vector2D(a.x + b, a.y + b);
}

Vector2D operator+(const Vector2D& a, double b)
{
	return Vector2D(a.x + b, a.y + b);
}

Vector2D operator-(const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.x - b.x, a.y - b.y);
}

Vector2D operator-(const Vector2D& a, float b)
{
	return Vector2D(a.x - b, a.y - b);
}

Vector2D operator-(const Vector2D& a, double b)
{
	return Vector2D(a.x - b, a.y - b);
}

Vector2D operator-(double b, const Vector2D& a)
{
	return Vector2D(b - a.x, b - a.y);
}

Vector2D operator*(const Vector2D& a, float b)
{
	return Vector2D(a.x * b, a.y * b);
}

Vector2D operator*(const Vector2D& a, double b)
{
	return Vector2D(a.x * b, a.y * b);
}

Vector2D operator*(double a, const Vector2D& b)
{
	return Vector2D(b.x * a, b.y * a);
}

Vector2D operator/(const Vector2D& a, double b)
{
	return Vector2D(a.x / b, a.y / b);
}
Vector2D operator/(double a, const Vector2D& b)
{
	return Vector2D(b.x / a, b.y / a);
}

Vector2D operator/(const Vector2D& a, float b)
{
	return Vector2D(a.x / b, a.y / b);
}

Vector2D operator/(float a, const Vector2D& b)
{
	return Vector2D(b.x / a, b.y / a);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2D& Vector2D::operator*=(const float& other)
{
	x *= other;
	y *= other;

	return *this;
}

Vector2D& Vector2D::operator*=(const double& other)
{
	x *= other;
	y *= other;

	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

Vector2D& Vector2D::operator/=(const double& other)
{
	x /= other;
	y /= other;

	return *this;
}

float Vector2D::toRadians() const
{
	return std::atan2(y, x);
}

std::ostream& operator<<(std::ostream& outstream, const Vector2D& vector)
{
	return (outstream << "Vector2 - x: " << vector.x << ", y:" << vector.y << ";");
}

Vector2D Vector2D::normalize(const Vector2D& vector)
{
	const float magnitude = vector.magnitude();

	return Vector2D(
		vector.x / magnitude,
		vector.y / magnitude);
}

float Vector2D::distance(const Vector2D& source, const Vector2D& target)
{
	return sqrt(
		(target.x - source.x) * (target.x - source.x) +
		(target.y - source.y) * (target.y - source.y));
}

float Vector2D::distanceSqrt(const Vector2D& source, const Vector2D& target)
{
	return
		(target.x - source.x) * (target.x - source.x) +
		(target.y - source.y) * (target.y - source.y);
}