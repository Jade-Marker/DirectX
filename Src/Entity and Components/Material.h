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
	bool _isTransparent;

public:
	Material(Shader* shader, std::vector<Texture*> textures, bool isTransparent);

	Shader* const GetShader();
	const std::vector<Texture*>& GetTextures();
	bool IsTransparent();
};

