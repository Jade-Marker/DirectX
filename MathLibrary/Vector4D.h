#pragma once
#include "Vector3D.h"
class Vector4D
{
public:
	union {
		float values[4];
		struct { float x, y, z, w; };
	};

public:
	Vector4D();
	Vector4D(float x, float y, float z, float w);
	Vector4D(const Vector4D& vec);
	Vector4D(const Vector3D& vec, float w);
};

