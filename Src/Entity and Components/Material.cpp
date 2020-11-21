#include "Material.h"

Material::Material(Shader* shader, std::vector<Texture*> textures, bool isTransparent):
	_shader(shader), _textures(textures), _isTransparent(isTransparent)
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

bool Material::IsTransparent()
{
	return _isTransparent;
}
