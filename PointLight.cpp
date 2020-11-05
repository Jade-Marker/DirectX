#include "PointLight.h"

PointLight::PointLight(const XMFLOAT3& position, const XMFLOAT4& diffuseColor, const XMFLOAT4& ambientColor, const XMFLOAT4& specularColor,
    float specularPower, float diffuseStrength, float ambientStrength, float specularStrength):
    Light(XMFLOAT4(position.x, position.y, position.z, 1.0f), XMFLOAT4(0,0,0,0), diffuseColor, ambientColor, specularColor, specularPower, diffuseStrength, ambientStrength, specularStrength)
{
}
