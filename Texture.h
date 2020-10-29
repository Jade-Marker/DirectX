#pragma once
#include <d3d11_1.h>
#include "Shader.h"
#include "DDSTextureLoader.h"

class Texture
{
private:
	ID3D11Device* _pd3dDevice;
	ID3D11ShaderResourceView* _pTexture;
	ID3D11SamplerState* _pSamplerLinear;

public:
	Texture(ID3D11Device* pd3dDevice, const WCHAR* filePath);

	void Bind(Shader* shader, UINT slot);
};

