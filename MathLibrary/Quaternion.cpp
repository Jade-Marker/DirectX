#include "Quaternion.h"
#include "Matrix.h"
#include "Constants.h"
#include <math.h>

Quaternion::Quaternion():
	x(0), y(0), z(0), w(1)
{
}

Quaternion::Quaternion(float x, float y, float z, float w):
	x(x), y(y), z(z), w(w)
{
}

Quaternion::Quaternion(const Vector4D& vector):
	x(vector.x), y(vector.y), z(vector.z), w(vector.w)
{
}

Quaternion::Quaternion(const Vector3D& vector, float w):
	x(vector.x), y(vector.y), z(vector.z), w(w)
{
}

Matrix Quaternion::ToRotationMatrix() const
{
	Matrix result;

	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;

	result.rows[0][0] = 1.0f - 2.0f * y2 - 2.0f * z2;
	result.rows[0][1] = 2.0f * (x * y - w * z);
	result.rows[0][2] = 2.0f * (x * z + w * y);

	result.rows[1][0] = 2.0f * (x * y + w * z);
	result.rows[1][1] = 1.0f - 2.0f * x2 - 2.0f * z2;
	result.rows[1][2] = 2.0f * (y * z - w * x);

	result.rows[2][0] = 2.0f * (x * z - w * y);
	result.rows[2][1] = 2.0f * (y * z + w * x);
	result.rows[2][2] = 1.0f - 2.0f * x2 - 2.0f * y2;

	return result;
}

void Quaternion::Normalise()
{
	float magSquared = x * x + y * y + z * z + w * w;
	if (magSquared == 0)
	{
		w = 1;
	}
	else
	{
		float scale = 1.0f / (sqrtf(magSquared));

		x *= scale;
		y *= scale;
		z *= scale;
		w *= scale;
	}

}

Vector3D Quaternion::ToEuler() const
{
	//Todo, get the x and z components added to this
	Vector3D result;

	result.y = AngleAboutY();

	return result;
}

float Quaternion::AngleAboutY() const
{
	Matrix rotationMatrix = ToRotationMatrix();
	Vector3D xAxis = rotationMatrix * Vector3D(1, 0, 0);

	float hypotenuse = sqrtf(xAxis.x * xAxis.x + xAxis.z * xAxis.z);
	float tanAngle = xAxis.z / xAxis.x;
	float sinAngle = xAxis.z / hypotenuse;
	float cosAngle = xAxis.x / hypotenuse;

	float angle = asinf(sinAngle);

	bool sinPos = !signbit(sinAngle);
	bool cosPos = !signbit(cosAngle);
	bool tanPos = !signbit(tanAngle);

	if (sinPos && !cosPos && !tanPos)
		angle = cPI - angle;
	else if (tanPos && !sinPos && !cosPos)
		angle = cPI + -angle;
	else if (cosPos && !sinPos && !tanPos)
		angle = cPI2 + angle;

	return angle;
}

Quaternion Quaternion::Conjugate()
{
	return Quaternion(-x, -y, -z, w);
}

void Quaternion::RotateByVector(const Vector3D& vector)
{
	Quaternion q = Quaternion(vector, 0);
	q = *this * q;

	w += q.w * 0.5f;
	x += q.x * 0.5f;
	y += q.y * 0.5f;
	z += q.z * 0.5f;

	Normalise();
}

Quaternion Quaternion::operator*(const Quaternion& value)
{
	Quaternion result;

	Quaternion q = *this;
	result.w = q.w * value.w - q.x * value.x -
		q.y * value.y - q.z * value.z;
	result.x = q.w * value.x + q.x * value.w +
		q.y * value.z - q.z * value.y;
	result.y = q.w * value.y + q.y * value.w +
		q.z * value.x - q.x * value.z;
	result.z = q.w * value.z + q.z * value.w +
		q.x * value.y - q.y * value.x;

	return result;
}

Quaternion& Quaternion::operator*=(const Quaternion& value)
{
	Quaternion q = *this;

	w = q.w * value.w - q.x * value.x -
		q.y * value.y - q.z * value.z;
	x = q.w * value.x + q.x * value.w +
		q.y * value.z - q.z * value.y;
	y = q.w * value.y + q.y * value.w +
		q.z * value.x - q.x * value.z;
	z = q.w * value.z + q.z * value.w +
		q.x * value.y - q.y * value.x;

	return *this;
}

Quaternion Quaternion::EulerToQuaternion(const Vector3D& eulerAngles)
{
	float cosZ, sinZ, cosY, sinY, cosX, sinX;
	cosZ = cosf(eulerAngles.z * 0.5f);
	sinZ = sinf(eulerAngles.z * 0.5f);
	cosY = cosf(eulerAngles.y * 0.5f);
	sinY = sinf(eulerAngles.y * 0.5f);
	cosX = cosf(eulerAngles.x * 0.5f);
	sinX = sinf(eulerAngles.x * 0.5f);

	Quaternion quaternion = Quaternion(
		sinX * cosY * cosZ + cosX * sinY * sinZ,
		cosX * sinY * cosZ + sinX * cosY * sinZ,
		cosX * cosY * sinZ - sinX * sinY * cosZ,
		cosX * cosY * cosZ - sinX * sinY * sinZ);

	return quaternion;
}

Quaternion Quaternion::EulerToQuaternion(float x, float y, float z)
{
	return EulerToQuaternion(Vector3D(x, y, z));
}
