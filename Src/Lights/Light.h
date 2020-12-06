#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Light
{
private:
	XMFLOAT4 _diffuseColor;
	XMFLOAT4 _ambientColor;
	XMFLOAT4 _specularColor;
	XMFLOAT4 _position;
	XMFLOAT4 _direction;
	float	 _specularPower;
	float _diffuseStrength;
	float _ambientStrength;
	float _specularStrength;

public:
	Light(const XMFLOAT4& position, const XMFLOAT4& direction, const XMFLOAT4& diffuseColor, const XMFLOAT4& ambientColor, const XMFLOAT4& specularColor,
		float specularPower, float diffuseStrength, float ambientStrength, float specularStrength);
	Light();

	const XMFLOAT4& GetPosition();
	const XMFLOAT4& GetDirection();
	const XMFLOAT4& GetDiffuseColor();
	const XMFLOAT4& GetAmbientColor();
	const XMFLOAT4& GetSpecularColor();

	float GetSpecularPower();
	float GetDiffuseStrength();
	float GetAmbientStrength();
	float GetSpecularStrength();

	const void* GetData();

	void SetDiffuse(const XMFLOAT4& diffuseColor);
	void SetAmbient(const XMFLOAT4& ambientColor);
	void SetSpecular(const XMFLOAT4& specularColor);
	void SetPosition(const XMFLOAT4& position);
	void SetDirection(const XMFLOAT4& direction);

	void SetSpecularPower(float specularPower);
	void SetDiffuseStrength(float diffuseStrength);
	void SetAmbientStrength(float ambientStrength);
	void SetSpecularStrength(float specularStrength);
};

