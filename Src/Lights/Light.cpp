#include "Light.h"

Light::Light(const XMFLOAT4& position, const XMFLOAT4& direction, const XMFLOAT4& diffuseColor, const XMFLOAT4& ambientColor, const XMFLOAT4& specularColor,
    float specularPower, float diffuseStrength, float ambientStrength, float specularStrength):
    _position(position), _direction(direction), _diffuseColor(diffuseColor), _ambientColor(ambientColor), _specularColor(specularColor), _specularPower(specularPower),
    _diffuseStrength(diffuseStrength), _ambientStrength(ambientStrength), _specularStrength(specularStrength)
{
}

Light::Light():
    _position(XMFLOAT4(0,0,0,0)), _direction(XMFLOAT4(0, 0, 0, 0)), _diffuseColor(XMFLOAT4(0, 0, 0, 0)), _ambientColor(XMFLOAT4(0, 0, 0, 0)), 
    _specularColor(XMFLOAT4(0, 0, 0, 0)), _specularPower(0.0f), _diffuseStrength(0.0f), _ambientStrength(0.0f), _specularStrength(0.0f)
{
}

const XMFLOAT4& Light::GetPosition()
{
    return _position;
}

const XMFLOAT4& Light::GetDirection()
{
    return _direction;
}

const XMFLOAT4& Light::GetDiffuseColor()
{
    return _diffuseColor;
}

const XMFLOAT4& Light::GetAmbientColor()
{
    return _ambientColor;
}

const XMFLOAT4& Light::GetSpecularColor()
{
    return _specularColor;
}

float Light::GetSpecularPower()
{
    return _specularPower;
}

float Light::GetDiffuseStrength()
{
    return _diffuseStrength;
}

float Light::GetAmbientStrength()
{
    return _ambientStrength;
}

float Light::GetSpecularStrength()
{
    return _specularStrength;
}

const void* Light::GetData()
{
	return &_diffuseColor;
}

void Light::SetDiffuse(const XMFLOAT4& diffuseColor)
{
    _diffuseColor = diffuseColor;
}

void Light::SetAmbient(const XMFLOAT4& ambientColor)
{
    _ambientColor = ambientColor;
}

void Light::SetSpecular(const XMFLOAT4& specularColor)
{
    _specularColor = specularColor;
}

void Light::SetPosition(const XMFLOAT4& position)
{
    _position = position;
}

void Light::SetDirection(const XMFLOAT4& direction)
{
    _direction = direction;
}

void Light::SetSpecularPower(float specularPower)
{
    _specularPower = specularPower;
}

void Light::SetDiffuseStrength(float diffuseStrength)
{
    _diffuseStrength = diffuseStrength;
}

void Light::SetAmbientStrength(float ambientStrength)
{
    _ambientStrength = ambientStrength;
}

void Light::SetSpecularStrength(float specularStrength)
{
    _specularStrength = specularStrength;
}
