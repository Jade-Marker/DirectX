#include "Vector2D.h"

Vector2D::Vector2D():
	x(0), y(0)
{
}

Vector2D::Vector2D(float x, float y):
	x(x), y(y)
{
}

Vector2D::Vector2D(const Vector2D& vec) :
	x(vec.x), y(vec.y)
{
}
