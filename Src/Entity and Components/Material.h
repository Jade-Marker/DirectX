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
	Vector4D _diffuseMtrl;
	Vector4D _ambientMtrl;
	Vector4D _specularMtrl;


public:
	Material(Shader* pShader, Texture* pDiffuse, Texture* pAmbient, Texture* pSpecular, bool isTransparent, Vector4D diffuseMtrl, Vector4D ambientMtrl, Vector4D specularMtrl);

	Shader* const GetShader();
	Texture* const GetDiffuseTexture();
	Texture* const GetAmbientTexture();
	Texture* const GetSpecularTexture();
	const Vector4D& GetDiffuseMaterial();
	const Vector4D& GetAmbientMaterial();
	const Vector4D& GetSpecularMaterial();

	bool IsTransparent();
};