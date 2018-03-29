#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <string>
#include <sstream>

class Vector2D
{
public:
	float x;
	float y;
	float w;

	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();
	void add(const Vector2D& other);
	void add(const float x, const float y);
	float magnitude() const;
	float magnitudeSqrt() const;
	float dotProduct(const Vector2D& other) const;
	void normalize();
	void clamp(float magnitude);
	std::string toString() const;
	friend std::ostream& operator<<(std::ostream& outstream, const Vector2D& vector);
	friend Vector2D operator+(const Vector2D& a, const Vector2D& b);
	friend Vector2D operator+(const Vector2D& a, float b);
	friend Vector2D operator+(const Vector2D& a, double b);
	friend Vector2D operator-(const Vector2D& a, const Vector2D& b);
	friend Vector2D operator-(const Vector2D& a, float b);
	friend Vector2D operator-(const Vector2D& a, double b);
	friend Vector2D operator-(double b, const Vector2D& a);
	friend Vector2D operator*(double a, const Vector2D& b);
	friend Vector2D operator*(const Vector2D& a, float b);
	friend Vector2D operator*(const Vector2D& a, double b);
	friend Vector2D operator/(double a, const Vector2D& b);
	friend Vector2D operator/(const Vector2D& a, double b);
	friend Vector2D operator/(float a, const Vector2D& b);
	friend Vector2D operator/(const Vector2D& a, float b);
	Vector2D& operator+=(const Vector2D &other);
	Vector2D& operator-=(const Vector2D &other);
	Vector2D& operator*=(const float& other);
	Vector2D& operator*=(const double& other);
	Vector2D& operator*=(const Vector2D &other);
	Vector2D& operator/=(const Vector2D &other);
	Vector2D& operator/=(const double& other);
	bool operator!=(const Vector2D& other);
	bool operator==(const Vector2D& other);
	float toRadians() const;
	static Vector2D normalize(const Vector2D& vector);
	static float distance(const Vector2D& source, const Vector2D& target);
	static float distanceSqrt(const Vector2D& source, const Vector2D& target);
	static Vector2D perpendicular(const Vector2D& vector);
	static Vector2D rotateAroundOrigin(const Vector2D& vector, float rotation);
};

#endif