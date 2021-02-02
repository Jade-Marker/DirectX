#include "Quaternion.h"
#include "Matrix.h"
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

Matrix Quaternion::ToRotationMatrix()
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
