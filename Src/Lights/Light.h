#pragma once
#include <MathLibrary\Vector4D.h>

class Light
{
private:
	Vector4D _diffuseColor;
	Vector4D _ambientColor;
	Vector4D _specularColor;
	Vector4D _position;
	Vector4D _direction;
	float	 _specularPower;
	float _diffuseStrength;
	float _ambientStrength;
	float _specularStrength;

public:
	Light(const Vector4D& position, const Vector4D& direction, const Vector4D& diffuseColor, const Vector4D& ambientColor, const Vector4D& specularColor,
		float specularPower, float diffuseStrength, float ambientStrength, float specularStrength);
	Light();

	const Vector4D& GetPosition();
	const Vector4D& GetDirection();
	const Vector4D& GetDiffuseColor();
	const Vector4D& GetAmbientColor();
	const Vector4D& GetSpecularColor();

	float GetSpecularPower();
	float GetDiffuseStrength();
	float GetAmbientStrength();
	float GetSpecularStrength();

	void SetDiffuse(const Vector4D& diffuseColor);
	void SetAmbient(const Vector4D& ambientColor);
	void SetSpecular(const Vector4D& specularColor);
	void SetPosition(const Vector4D& position);
	void SetDirection(const Vector4D& direction);

	void SetSpecularPower(float specularPower);
	void SetDiffuseStrength(float diffuseStrength);
	void SetAmbientStrength(float ambientStrength);
	void SetSpecularStrength(float specularStrength);
};

