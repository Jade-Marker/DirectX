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
	Quaternion(const Vector3D& vector, float w);

	Matrix ToRotationMatrix() const;
	void Normalise();
	Vector3D ToEuler() const;
	float AngleAboutY() const;

	Quaternion Conjugate();
	void RotateByVector(const Vector3D& vector);

	Quaternion operator*(const Quaternion& value);
	Quaternion& operator*=(const Quaternion& value);

	static Quaternion EulerToQuaternion(const Vector3D& eulerAngles);
	static Quaternion EulerToQuaternion(float x, float y, float z);
};

