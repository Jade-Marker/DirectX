#pragma once

class Vector4D;

class Vector3D
{
public:
    union {
        float values[3];
        struct { float x, y, z; };
    };
	
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& vec);

    Vector3D operator+(const Vector3D& vec);  
    Vector3D& operator+=(const Vector3D& vec);
    Vector3D operator-(const Vector3D& vec);  
    Vector3D& operator-=(const Vector3D& vec);
    Vector3D operator*(float value);  
    Vector3D& operator*=(float value);
    Vector3D operator/(float value);  
    Vector3D& operator/=(float value);
    Vector3D& operator=(const Vector3D& vec);

    float Dot(const Vector3D& vec);
    Vector3D Cross(const Vector3D& vec);
    void Normalise();
    float Square();
    float Dist(const Vector3D& vec);
    float Magnitude();

    Vector4D ToQuaterion() const;
};
