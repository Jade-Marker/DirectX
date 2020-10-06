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

	XMFLOAT3 _position;
	XMFLOAT3 _angle;
	XMFLOAT3 _tScale;
	float _t;

public:
	Cube(XMFLOAT3 position, XMFLOAT3 angle, XMFLOAT3 tScale,
		ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, ID3D11VertexShader* pVertexShader, ID3D11PixelShader* pPixelShader, ID3D11Buffer* pConstantBuffer);
	void Draw(XMFLOAT4X4 view, XMFLOAT4X4 projection);
	void Update();

private:
	HRESULT InitVertexBuffer();
	HRESULT InitIndexBuffer();
	void BindBuffers();
};

