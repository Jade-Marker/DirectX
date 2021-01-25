#include "Vector3D.h"
#include <cmath>


Vector3D::Vector3D():
	x(0), y(0), z(0)
{
}

Vector3D::Vector3D(float x, float y, float z):
	x(x), y(y), z(z)
{
	
}

Vector3D::Vector3D(const Vector3D& vec):
	x(vec.x), y(vec.y), z(vec.z)
{
}

Vector3D Vector3D::operator+(const Vector3D& vec)
{
	return Vector3D(x + vec.x, y + vec.y, z + vec.z);
}

Vector3D& Vector3D::operator+=(const Vector3D& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& vec)
{
	return Vector3D(x - vec.x, y - vec.y, z - vec.z);
}

Vector3D& Vector3D::operator-=(const Vector3D& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

Vector3D Vector3D::operator*(float value)
{
	return Vector3D(x * value, y * value, z * value);
}

Vector3D& Vector3D::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Vector3D Vector3D::operator/(float value)
{
	return Vector3D(x / value, y / value, z / value);
}

Vector3D& Vector3D::operator/=(float value)
{
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

Vector3D& Vector3D::operator=(const Vector3D& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;

	return *this;
}

float Vector3D::Dot(const Vector3D& vec)
{
	return (x * vec.x) + (y * vec.y) + (z * vec.z);
}

Vector3D Vector3D::Cross(const Vector3D& vec)
{
	return Vector3D(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

void Vector3D::Normalise()
{
	*this /= Square();
}

float Vector3D::Square()
{
	return (x * x) + (y * y) + (z * z);
}

float Vector3D::Dist(const Vector3D& vec)
{
	return (*this-vec).Magnitude();
}

float Vector3D::Magnitude()
{
	return sqrt(Square());
}