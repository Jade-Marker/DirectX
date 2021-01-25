#include "Vector4D.h"

Vector4D::Vector4D():
	x(0), y(0), z(0), w(0)
{
}

Vector4D::Vector4D(float x, float y, float z, float w):
	x(x), y(y), z(z), w(w)
{
}

Vector4D::Vector4D(const Vector4D& vec):
	x(vec.x), y(vec.y), z(vec.z), w(vec.w)
{
}

Vector4D::Vector4D(const Vector3D& vec, float w):
	x(vec.x), y(vec.y), z(vec.z), w(w)
{
}
