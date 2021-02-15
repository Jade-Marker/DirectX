#include "Transform.h"

Transform::Transform(const Vector3D& position, const Quaternion& rotation, const Vector3D& scale)
{
	Position = position;
	Rotation = rotation;
	Scale = scale;
}

Transform::Transform()
{
	Position = Vector3D();
	Rotation = Quaternion();
	Scale = Vector3D();
}

void Transform::Translate(const Vector3D& translation)
{
	Position += translation;
}

void Transform::Rotate(Quaternion rotation)
{
	Rotation *= rotation;
}

void Transform::EulerRotate(const Vector3D& rotation)
{
	Rotate(Quaternion::EulerToQuaternion(rotation));
}

Matrix Transform::GetWorldMatrix()
{
	return Matrix::Translate(Position) * GetRotationMatrix() * Matrix::Scale(Scale);
}

Matrix Transform::GetRotationMatrix()
{
	return Rotation.ToRotationMatrix();
}
