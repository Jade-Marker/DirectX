#include "PointLight.h"

PointLight::PointLight(const Vector3D& position, const Vector4D& diffuseColor, const Vector4D& ambientColor, const Vector4D& specularColor,
    float specularPower, float diffuseStrength, float ambientStrength, float specularStrength):
    Light(Vector4D(position, 1.0f), Vector4D(0,0,0,0), diffuseColor, ambientColor, specularColor, specularPower, diffuseStrength, ambientStrength, specularStrength)
{
}
