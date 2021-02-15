#pragma once
#include <MathLibrary\Vector3D.h>
#include <MathLibrary\Matrix.h>
struct Transform
{
	Vector3D Position;
	Quaternion Rotation;
	Vector3D Scale;

	Transform(const Vector3D& position, const Quaternion& rotation, const Vector3D& scale);
	Transform();

	void Translate(const Vector3D& translation);

	void Rotate(Quaternion rotation);

	void EulerRotate(const Vector3D& rotation);

	Matrix GetWorldMatrix();

	Matrix GetRotationMatrix();
};

