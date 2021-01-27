#include "Matrix.h"

inline void Matrix::CopyValues(const Matrix& mat)
{
	for (int i = 0; i < 16; i++)
		values[i] = mat.values[i];
}

Matrix::Matrix():
	values{ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 }
{
}

Matrix::Matrix(const float& initialValue):
	values{
	initialValue, initialValue, initialValue, initialValue, 
	initialValue, initialValue, initialValue, initialValue, 
	initialValue, initialValue, initialValue, initialValue, 
	initialValue, initialValue, initialValue, initialValue}
{
}

Matrix::Matrix(const float initialValues[16])
{
	for (int i = 0; i < 16; i++)
		values[i] = initialValues[i];
}

Matrix::Matrix(const Matrix& mat):
	values()
{
	CopyValues(mat);
}

Matrix& Matrix::operator=(const Matrix& mat)
{
	CopyValues(mat);

	return *this;
}

Matrix Matrix::operator+(const Matrix& mat)
{
	Matrix result;

	for (int i = 0; i < 16; i++)
	{
		result.values[i] = values[i] + mat.values[i];
	}

	return result;
}

Matrix& Matrix::operator+=(const Matrix& mat)
{
	for (int i = 0; i < 16; i++)
	{
		values[i] += mat.values[i];
	}

	return *this;
}

Matrix Matrix::operator-(const Matrix& mat)
{
	Matrix result;

	for (int i = 0; i < 16; i++)
	{
		result.values[i] = values[i] - mat.values[i];
	}

	return result;
}

Matrix& Matrix::operator-=(const Matrix& mat)
{
	for (int i = 0; i < 16; i++)
	{
		values[i] -= mat.values[i];
	}

	return *this;
}

Matrix Matrix::operator*(const Matrix& mat)
{
	Matrix result;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float value = 0;
			for (int k = 0; k < 4; k++)
			{
				value += rows[i][k] * mat.rows[k][j];
			}

			result.rows[i][j] = value;
		}
	}

	return result;
}

Matrix& Matrix::operator*=(const Matrix& mat)
{
	Matrix result = Matrix(*this);

	result = result * mat;

	CopyValues(result);

	return *this;
}

bool Matrix::operator==(const Matrix& mat)
{
	for (int i = 0; i < 16; i++)
	{
		if (values[i] != mat.values[i])
			return false;
	}

	return true;
}

bool Matrix::operator!=(const Matrix& mat)
{
	for (int i = 0; i < 16; i++)
	{
		if (values[i] != mat.values[i])
			return true;
	}

	return false;
}

Matrix Matrix::operator*(const float& value)
{
	Matrix result;

	for (int i = 0; i < 16; i++)
		result.values[i] = values[i] * value;

	return result;
}

Matrix& Matrix::operator*=(const float& value)
{
	for (int i = 0; i < 16; i++)
	{
		values[i] *= value;
	}

	return *this;
}

Vector3D Matrix::operator*(const Vector3D& vec)
{
	Vector4D temp = Vector4D(vec, 1);
	temp = *this * temp;

	Vector3D result = Vector3D(temp.x, temp.y, temp.z);

	return result;
}

Vector4D Matrix::operator*(const Vector4D& vec)
{
	Vector4D result;

	for (int i = 0; i < 4; i++)
	{
		float value = 0;

		for (int j = 0; j < 4; j++)
		{
			value += rows[i][j] * vec.values[j];
		}

		result.values[i] = value;
	}

	return result;
}

void Matrix::Transpose()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = i; j < 4; j++)
		{
			float temp;

			temp = rows[i][j];

			rows[i][j] = rows[j][i];

			rows[j][i] = temp;
		}
	}
}

void Matrix::SwapRows(int rowNum, int otherRow)
{
	for (int i = 0; i < 4; i++)
	{
		float tempValue;

		tempValue = rows[rowNum][i];

		rows[rowNum][i] = rows[otherRow][i];

		rows[otherRow][i] = tempValue;
	}

}

Matrix Matrix::Inverse()
{
	Matrix temporaryMatrix = Matrix(values);
	Matrix augmentedMatrix = Matrix();

	for (int j = 0; j < 4; j++)
	{
		float value = 0;
		int maxIndex = -1;

		for (int i = j; i < 4; i++)
		{
			if (abs(temporaryMatrix.rows[i][j]) > value)
			{
				value = abs(temporaryMatrix.rows[i][j]);
				maxIndex = i;
			}
		}

		if (maxIndex == -1)
			throw std::exception("Matrix has no inverse");
		else
		{
			float scalar = 1.0f / (temporaryMatrix.rows[maxIndex][j]);
			for (int i = 0; i < 4; i++)
			{
				temporaryMatrix.rows[maxIndex][i] *= scalar;
				augmentedMatrix.rows[maxIndex][i] *= scalar;
			}

			if (j != maxIndex)
			{
				temporaryMatrix.SwapRows(j, maxIndex);
				augmentedMatrix.SwapRows(j, maxIndex);
			}

			for (int i = 0; i < 4; i++)
			{
				if (i != j)
				{
					float rowScalar = -temporaryMatrix.rows[i][j];

					for (int k = 0; k < 4; k++)
					{
						temporaryMatrix.rows[i][k] += rowScalar * temporaryMatrix.rows[j][k];
						augmentedMatrix.rows[i][k] += rowScalar * augmentedMatrix.rows[j][k];
					}
				}
			}
		}
	}
	

	return augmentedMatrix;
}

Matrix Matrix::Translate(const Vector3D& offsets)
{
	Matrix result = Matrix();

	result.rows[0][3] = offsets.x;
	result.rows[1][3] = offsets.y;
	result.rows[2][3] = offsets.z;

	return result;
}

Matrix Matrix::Rotate(const Vector3D& angles)
{
	Matrix result;

	Vector4D quaternion = angles.ToQuaterion();

	float x2 = quaternion.x * quaternion.x;
	float y2 = quaternion.y * quaternion.y;
	float z2 = quaternion.z * quaternion.z;

	result.rows[0][0] = 1.0f - 2.0f * y2 - 2.0f * z2;
	result.rows[0][1] = 2.0f * (quaternion.x * quaternion.y - quaternion.w * quaternion.z);
	result.rows[0][2] = 2.0f * (quaternion.x * quaternion.z + quaternion.w * quaternion.y);

	result.rows[1][0] = 2.0f * (quaternion.x * quaternion.y + quaternion.w * quaternion.z);
	result.rows[1][1] = 1.0f - 2.0f * x2 - 2.0f * z2;
	result.rows[1][2] = 2.0f * (quaternion.y * quaternion.z - quaternion.w * quaternion.x);

	result.rows[2][0] = 2.0f * (quaternion.x * quaternion.z - quaternion.w * quaternion.y);
	result.rows[2][1] = 2.0f * (quaternion.y * quaternion.z + quaternion.w * quaternion.x);
	result.rows[2][2] = 1.0f - 2.0f * x2 - 2.0f * y2;

	return result;
}

Matrix Matrix::RotateX(float angle)
{
	Matrix result = Matrix();

	result.rows[1][1] = cos(angle);
	result.rows[1][2] = -sin(angle);
	result.rows[2][1] = sin(angle);
	result.rows[2][2] = cos(angle);

	return result;
}

Matrix Matrix::RotateY(float angle)
{
	Matrix result = Matrix();

	result.rows[0][0] = cos(angle);
	result.rows[0][2] = sin(angle);
	result.rows[2][0] = -sin(angle);
	result.rows[2][2] = cos(angle);

	return result;
}

Matrix Matrix::RotateZ(float angle)
{
	Matrix result = Matrix();

	result.rows[0][0] = cos(angle);
	result.rows[0][1] = -sin(angle);
	result.rows[1][0] = sin(angle);
	result.rows[1][1] = cos(angle);

	return result;
}

Matrix Matrix::Scale(const Vector3D& scales)
{
	Matrix result = Matrix();

	result.rows[0][0] = scales.x;
	result.rows[1][1] = scales.y;
	result.rows[2][2] = scales.z;

	return result;
}

Matrix Matrix::PerspectiveFovLH(float fovAngleY, float aspect, float nearZ, float farZ)
{
	Matrix result = Matrix();

	float yScale = cos(fovAngleY/2.0f) / sin(fovAngleY/2.0f);
	float xScale = yScale / aspect;

	result.rows[0][0] = xScale;
	result.rows[1][1] = yScale;
	result.rows[2][2] = farZ / (farZ - nearZ);
	result.rows[3][2] = 1.0f;
	result.rows[2][3] = -nearZ * farZ/(farZ - nearZ);
	result.rows[3][3] = 0.0f;


	return result;
}
