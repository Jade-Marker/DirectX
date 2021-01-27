#include "Material.h"

Material::Material(Shader* pShader, Texture* pDiffuse, Texture* pAmbient, Texture* pSpecular, bool isTransparent, Vector4D diffuseMtrl, Vector4D ambientMtrl, Vector4D specularMtrl):
	_pShader(pShader), _pDiffuse(pDiffuse), _pAmbient(pAmbient), _pSpecular(pSpecular), _isTransparent(isTransparent), _diffuseMtrl(diffuseMtrl), _ambientMtrl(ambientMtrl), _specularMtrl(specularMtrl)
{
}

Shader* const Material::GetShader()
{
	return _pShader;
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

const Vector4D& Material::GetDiffuseMaterial()
{
	return _diffuseMtrl;
}

const Vector4D& Material::GetAmbientMaterial()
{
	return _ambientMtrl;
}

const Vector4D& Material::GetSpecularMaterial()
{
	return _specularMtrl;
}

bool Material::IsTransparent()
{
	return _isTransparent;
}
