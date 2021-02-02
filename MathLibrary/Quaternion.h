#pragma once
#include "Vector4D.h"

class Matrix;

class Quaternion
{
public:
	float x, y, z, w;

public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Vector4D& vector);

	Matrix ToRotationMatrix();

	static Quaternion EulerToQuaternion(const Vector3D& eulerAngles);
};

