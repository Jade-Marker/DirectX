#include "Light.h"

Light::Light(const XMFLOAT4& position, const XMFLOAT4& direction, const XMFLOAT4& diffuseColor, const XMFLOAT4& ambientColor, const XMFLOAT4& specularColor,
    float specularPower, float diffuseStrength, float ambientStrength, float specularStrength):
    _position(position), _direction(direction), _diffuseColor(diffuseColor), _ambientColor(ambientColor), _specularColor(specularColor), _specularPower(specularPower),
    _diffuseStrength(diffuseStrength), _ambientStrength(ambientStrength), _specularStrength(specularStrength)
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
