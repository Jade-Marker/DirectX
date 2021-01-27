#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight(const Vector3D& position, const Vector4D& diffuseColor, const Vector4D& ambientColor, const Vector4D& specularColor,
		float specularPower, float diffuseStrength, float ambientStrength, float specularStrength);
};

