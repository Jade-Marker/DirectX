#pragma once
#include <d3d11_1.h>
#include "Shader.h"
#include "DDSTextureLoader.h"
#include "DeviceManager.h"

class Texture
{
private:
	ID3D11ShaderResourceView* _pTexture;
	ID3D11SamplerState* _pSamplerLinear;

public:
	Texture(const WCHAR* filePath);
	~Texture();

	void Bind(Shader* shader, UINT slot);
};

