#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Vector3D& direction, const Vector4D& diffuseColor, const Vector4D& ambientColor, const Vector4D& specularColor,
    float specularPower, float diffuseStrength, float ambientStrength, float specularStrength):
    Light(Vector4D(0, 0, 0, 0), Vector4D(direction, 1.0f), diffuseColor, ambientColor, specularColor, specularPower, diffuseStrength, ambientStrength, specularStrength)
{
}
