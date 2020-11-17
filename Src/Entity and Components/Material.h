#pragma once
#include <vector>
#include "Component.h"
#include "Shader.h"
#include "Texture.h"
class Material : public Component
{
private:
	Shader* _shader;
	std::vector<Texture*> _textures;

public:
	Material(Shader* shader, std::vector<Texture*> textures);

	Shader* const GetShader();
	const std::vector<Texture*>& GetTextures();
};

