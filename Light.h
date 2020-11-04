#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Light
{
private:
	XMFLOAT4 _position;
	XMFLOAT4 _diffuseColor;
	XMFLOAT4 _ambientColor;
	XMFLOAT4 _specularColor;
	float	 _specularPower;
	float _diffuseStrength;
	float _ambientStrength;
	float _specularStrength;

public:
	Light(const XMFLOAT4& position, const XMFLOAT4& diffuseColor, const XMFLOAT4& ambientColor, const XMFLOAT4& specularColor,
		float specularPower, float diffuseStrength, float ambientStrength, float specularStrength);

	const XMFLOAT4& GetPosition();
	const XMFLOAT4& GetDiffuseColor();
	const XMFLOAT4& GetAmbientColor();
	const XMFLOAT4& GetSpecularColor();

	float GetSpecularPower();
	float GetDiffuseStrength();
	float GetAmbientStrength();
	float GetSpecularStrength();
};

