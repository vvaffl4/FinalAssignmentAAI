#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <string>
#include <sstream>

class Vector3D
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();
	void add(const Vector3D& other);
	void add(const float x, const float y, const float z);
	float magnitude() const;
	float magnitudeSqrt() const;
	float dotProduct(const Vector3D& other) const;
	void normalize();
	void clamp(float magnitude);
	//	float distanceSqrt(const Vector3& other) const;
	std::string toString() const;
	friend std::ostream& operator<<(std::ostream& outstream, const Vector3D& vector);
	friend Vector3D operator+(const Vector3D& a, const Vector3D& b);
	friend Vector3D operator-(const Vector3D& a, const Vector3D& b);
	Vector3D& operator+=(const Vector3D &other);
	Vector3D& operator-=(const Vector3D &other);
	Vector3D& operator*=(const Vector3D &other);
	Vector3D& operator/=(const Vector3D &other);
	//	Vector3& operator+=(const Vector3& other);
	static Vector3D normalize(const Vector3D& vector);
	static float distance(const Vector3D& source, const Vector3D& target);
	static float distanceSqrt(const Vector3D& source, const Vector3D& target);
	static Vector3D perpendicular(const Vector3D& vector);
	static Vector3D crossProduct(const Vector3D& source, const Vector3D& target);
	static float dotProduct(const Vector3D& source, const Vector3D& target);
};

#endif