#pragma once
class Vector2D
{
public:
	union {
		float values[2];
		struct { float x, y; };
	};

public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& vec);
};