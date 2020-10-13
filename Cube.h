#pragma once
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "Structures.h"

class Cube
{
private:
	ID3D11Device* _pd3dDevice;
	ID3D11DeviceContext* _pImmediateContext;
	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;
	ID3D11Buffer* _pVertexBuffer;
	ID3D11Buffer* _pIndexBuffer;
	ID3D11Buffer* _pConstantBuffer;
	ID3D11InputLayout* _pVertexLayout;
	ID3D11RasterizerState* _rasterState;
	ID3D11RasterizerState* _solidRasterState;
	ID3D11RasterizerState* _wireframeRasterState;

	bool _rasterKeyDown;
	bool _yDirState;
	bool _xDirState;


	XMFLOAT3 _position;
	XMFLOAT3 _angle;
	XMFLOAT3 _scale;
	XMFLOAT3 _tScale;
	float _t;

	SimpleVertex* vertexSource;
	UINT vertexCount;
	WORD* indexSource;
	UINT indexCount;

	Cube* _parent;

public:
	Cube(XMFLOAT3 position, XMFLOAT3 angle, XMFLOAT3 scale, XMFLOAT3 tScale, Cube* parent,
		ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, ID3D11Buffer* pConstantBuffer);
	void Draw(XMFLOAT4X4 view, XMFLOAT4X4 projection);
	void Update(float deltaTime);
	XMMATRIX GetWorldMatrix();

private:
	HRESULT InitVertexBuffer();
	HRESULT InitIndexBuffer();
	HRESULT InitShadersAndInputLayout();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	void BindBuffersAndLayout();
	void InitRasterState();

};

