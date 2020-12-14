#pragma once
#include <vector>
#include "Component.h"
#include "Shader.h"
#include "Texture.h"
class Material : public Component
{
private:
	Shader* _pShader;
	Texture* _pDiffuse;
	Texture* _pAmbient;
	Texture* _pSpecular;
	bool _isTransparent;
	XMFLOAT4 _diffuseMtrl;
	XMFLOAT4 _ambientMtrl;
	XMFLOAT4 _specularMtrl;


public:
	Material(Shader* pShader, Texture* pDiffuse, Texture* pAmbient, Texture* pSpecular, bool isTransparent, XMFLOAT4 diffuseMtrl, XMFLOAT4 ambientMtrl, XMFLOAT4 specularMtrl);

	Shader* const GetShader();
	Texture* const GetDiffuseTexture();
	Texture* const GetAmbientTexture();
	Texture* const GetSpecularTexture();
	const XMFLOAT4& GetDiffuseMaterial();
	const XMFLOAT4& GetAmbientMaterial();
	const XMFLOAT4& GetSpecularMaterial();

	bool IsTransparent();
};