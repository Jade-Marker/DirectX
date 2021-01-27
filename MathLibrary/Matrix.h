#pragma once
#include <exception>
#include "Vector3D.h"
#include "Vector4D.h"
class Matrix
{
public:
	union 
	{
		float values[16];
		struct { float rows[4][4]; };
	};

private:
	void inline CopyValues(const Matrix& mat);

public:
	Matrix();
	Matrix(const float& initialValue);
	Matrix(const float initialValues[16]);
	Matrix(const Matrix& mat);

	Matrix& operator=(const Matrix& mat);
	Matrix operator+(const Matrix& mat);
	Matrix& operator+=(const Matrix& mat);
	Matrix operator-(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);
	Matrix operator*(const Matrix& mat);
	Matrix& operator*=(const Matrix& mat);

	bool operator==(const Matrix& mat);
	bool operator!=(const Matrix& mat);

	Matrix operator*(const float& value);
	Matrix& operator*=(const float& value);

	Vector3D operator*(const Vector3D& vec);
	Vector4D operator*(const Vector4D& vec);

	void Transpose();
	void SwapRows(int rowNum, int otherRow);
	Matrix Inverse();

	static Matrix Translate(const Vector3D& offsets);
	static Matrix Rotate(const Vector3D& angles);
	static Matrix RotateX(float angle);
	static Matrix RotateY(float angle);
	static Matrix RotateZ(float angle);
	static Matrix Scale(const Vector3D& scales);

	static Matrix PerspectiveFovLH(float fovAngleY, float aspect, float nearZ, float farZ);
};

