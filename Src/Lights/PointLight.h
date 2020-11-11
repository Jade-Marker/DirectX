#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight(const XMFLOAT3& position, const XMFLOAT4& diffuseColor, const XMFLOAT4& ambientColor, const XMFLOAT4& specularColor,
		float specularPower, float diffuseStrength, float ambientStrength, float specularStrength);
};

