#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(const Vector3D& direction, const Vector4D& diffuseColor, const Vector4D& ambientColor, const Vector4D& specularColor,
		float specularPower, float diffuseStrength, float ambientStrength, float specularStrength);
};

