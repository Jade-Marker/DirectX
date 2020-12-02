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
	Texture();
	~Texture();

	void Load(const WCHAR* filePath);
	void Bind(Shader* shader, UINT slot);
	void Unbind(Shader* shader, UINT slot);

	static Texture* const GetDefault();
};