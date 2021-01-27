#include "Light.h"

Light::Light(const Vector4D& position, const Vector4D& direction, const Vector4D& diffuseColor, const Vector4D& ambientColor, const Vector4D& specularColor,
    float specularPower, float diffuseStrength, float ambientStrength, float specularStrength):
    _position(position), _direction(direction), _diffuseColor(diffuseColor), _ambientColor(ambientColor), _specularColor(specularColor), _specularPower(specularPower),
    _diffuseStrength(diffuseStrength), _ambientStrength(ambientStrength), _specularStrength(specularStrength)
{
}

Light::Light():
    _position(Vector4D(0,0,0,0)), _direction(Vector4D(0, 0, 0, 0)), _diffuseColor(Vector4D(0, 0, 0, 0)), _ambientColor(Vector4D(0, 0, 0, 0)),
    _specularColor(Vector4D(0, 0, 0, 0)), _specularPower(0.0f), _diffuseStrength(0.0f), _ambientStrength(0.0f), _specularStrength(0.0f)
{
}

const Vector4D& Light::GetPosition()
{
    return _position;
}

const Vector4D& Light::GetDirection()
{
    return _direction;
}

const Vector4D& Light::GetDiffuseColor()
{
    return _diffuseColor;
}

const Vector4D& Light::GetAmbientColor()
{
    return _ambientColor;
}

const Vector4D& Light::GetSpecularColor()
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

void Light::SetDiffuse(const Vector4D& diffuseColor)
{
    _diffuseColor = diffuseColor;
}

void Light::SetAmbient(const Vector4D& ambientColor)
{
    _ambientColor = ambientColor;
}

void Light::SetSpecular(const Vector4D& specularColor)
{
    _specularColor = specularColor;
}

void Light::SetPosition(const Vector4D& position)
{
    _position = position;
}

void Light::SetDirection(const Vector4D& direction)
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
