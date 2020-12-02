#include "Material.h"

Material::Material(Shader* pShader, Texture* pDiffuse, Texture* pAmbient, Texture* pSpecular, bool isTransparent, XMFLOAT4 diffuseMtrl, XMFLOAT4 ambientMtrl, XMFLOAT4 specularMtrl):
	_shader(pShader), _pDiffuse(pDiffuse), _pAmbient(pAmbient), _pSpecular(pSpecular), _isTransparent(isTransparent), _diffuseMtrl(diffuseMtrl), _ambientMtrl(ambientMtrl), _specularMtrl(specularMtrl)
{
}

Shader* const Material::GetShader()
{
	return _shader;
}

Texture* const Material::GetDiffuseTexture()
{
	return _pDiffuse;
}

Texture* const Material::GetAmbientTexture()
{
	return _pAmbient;
}

Texture* const Material::GetSpecularTexture()
{
	return _pSpecular;
}

const XMFLOAT4& Material::GetDiffuseMaterial()
{
	return _diffuseMtrl;
}

const XMFLOAT4& Material::GetAmbientMaterial()
{
	return _ambientMtrl;
}

const XMFLOAT4& Material::GetSpecularMaterial()
{
	return _specularMtrl;
}

bool Material::IsTransparent()
{
	return _isTransparent;
}
