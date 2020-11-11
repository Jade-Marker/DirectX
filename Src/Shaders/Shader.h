#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "DeviceManager.h"

class Shader
{
private:
	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;
	ID3D11InputLayout* _pVertexLayout;

private:
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

public:
	Shader(WCHAR* shaderSource, D3D11_INPUT_ELEMENT_DESC* layout, UINT numLayoutElements);
	~Shader();
	void SetInputLayout();
	void SetShader();
	void SetConstantBuffers(UINT startSlot, UINT numBuffers, ID3D11Buffer* const* constantBuffers);
	void SetShaderResources(UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* ppShaderResourceViews);
	void SetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers);
};

