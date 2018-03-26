#include "Vector3D.h"
#include <vector>


Vector3D::Vector3D() :
	x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{}

Vector3D::Vector3D(float x, float y, float z) :
	x(x), y(y), z(z), w(1.0f)
{}


Vector3D::~Vector3D()
{
}

void Vector3D::add(const Vector3D& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

void Vector3D::add(const float x, const float y, const float z)
{
	this->x += x;
	this->y += y;
	this->z += z;
}

float Vector3D::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3D::magnitudeSqrt() const
{
	return (x * x + y * y + z * z);
}

float Vector3D::dotProduct(const Vector3D& other) const
{
	return (x * other.x + y * other.y + z * other.z);
}

void Vector3D::normalize()
{
	float magnitude = sqrt(x * x + y * y + z * z);

	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

void Vector3D::clamp(float magnitude)
{
	float currentMagnitude = sqrt(x * x + y * y + z * z);

	if(currentMagnitude > magnitude)
	{
		normalize();
		x *= magnitude;
		y *= magnitude;
		z *= magnitude;
	}
}

Vector3D Vector3D::perpendicular(const Vector3D& vector)
{
	return Vector3D(-vector.y, vector.x, vector.z);
}

std::string Vector3D::toString() const
{
	std::stringstream input;
	input << "Vector2 - x: " << x << ", y:" << y << ", z:" << z << ";";
	return input.str();
}

Vector3D operator+(const Vector3D& a, const Vector3D& b)
{
	return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3D operator-(const Vector3D& a, const Vector3D& b)
{
	return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

Vector3D& Vector3D::operator/=(const Vector3D& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

std::ostream& operator<<(std::ostream& outstream, const Vector3D& vector)
{
	return (outstream << "Vector3 - x: " << vector.x << ", y:" << vector.y << ", z:" << vector.z << ";");
}

Vector3D Vector3D::normalize(const Vector3D& vector)
{
	float magnitude = vector.magnitude();

	return Vector3D(
		vector.x / magnitude,
		vector.y / magnitude,
		vector.z / magnitude);
}

float Vector3D::distance(const Vector3D& source, const Vector3D& target)
{
	return sqrt(
		(target.x - source.x) * (target.x - source.x) +
		(target.y - source.y) * (target.y - source.y) +
		(target.z - source.z) * (target.z - source.z));
}

float Vector3D::distanceSqrt(const Vector3D& source, const Vector3D& target)
{
	return
		(target.x - source.x) * (target.x - source.x) +
		(target.y - source.y) * (target.y - source.y) +
		(target.z - source.z) * (target.z - source.z);
}

Vector3D Vector3D::crossProduct(const Vector3D& source, const Vector3D& target)
{
	return Vector3D(
		source.y * target.z - source.z * target.y,
		source.z * target.x - source.x * target.z,
		source.x * target.y - source.y * target.x
	);
}

float Vector3D::dotProduct(const Vector3D& source, const Vector3D& target)
{
	return (source.x * target.x + source.y * target.y + source.z * target.z);
}