#include "Material.h"

Material::Material(Shader* shader, std::vector<Texture*> textures, bool isTransparent, XMFLOAT4 diffuseMtrl, XMFLOAT4 ambientMtrl, XMFLOAT4 specularMtrl):
	_shader(shader), _textures(textures), _isTransparent(isTransparent), _diffuseMtrl(diffuseMtrl), _ambientMtrl(ambientMtrl), _specularMtrl(specularMtrl)
{
}

Shader* const Material::GetShader()
{
	return _shader;
}

const std::vector<Texture*>& Material::GetTextures()
{
	return _textures;
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
