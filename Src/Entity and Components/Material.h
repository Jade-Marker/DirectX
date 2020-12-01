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
	XMFLOAT4 _diffuseMtrl;
	XMFLOAT4 _ambientMtrl;
	XMFLOAT4 _specularMtrl;


public:
	Material(Shader* shader, std::vector<Texture*> textures, bool isTransparent, XMFLOAT4 diffuseMtrl, XMFLOAT4 ambientMtrl, XMFLOAT4 specularMtrl);

	Shader* const GetShader();
	const std::vector<Texture*>& GetTextures();
	const XMFLOAT4& GetDiffuseMaterial();
	const XMFLOAT4& GetAmbientMaterial();
	const XMFLOAT4& GetSpecularMaterial();

	bool IsTransparent();
};

