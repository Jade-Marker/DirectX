#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const XMFLOAT3& direction, const XMFLOAT4& diffuseColor, const XMFLOAT4& ambientColor, const XMFLOAT4& specularColor,
    float specularPower, float diffuseStrength, float ambientStrength, float specularStrength):
    Light(XMFLOAT4(0, 0, 0, 0), XMFLOAT4(direction.x, direction.y, direction.z, 1.0f), diffuseColor, ambientColor, specularColor, specularPower, diffuseStrength, ambientStrength, specularStrength)
{
}
