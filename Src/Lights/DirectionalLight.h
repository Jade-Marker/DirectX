#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(const XMFLOAT3& direction, const XMFLOAT4& diffuseColor, const XMFLOAT4& ambientColor, const XMFLOAT4& specularColor,
		float specularPower, float diffuseStrength, float ambientStrength, float specularStrength);
};

