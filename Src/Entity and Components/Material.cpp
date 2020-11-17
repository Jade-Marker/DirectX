#include "Material.h"

Material::Material(Shader* shader, std::vector<Texture*> textures):
	_shader(shader), _textures(textures)
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
