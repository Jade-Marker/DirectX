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
	ID3D11DeviceContext* _pImmediateContext;
	D3D_DRIVER_TYPE _driverType;
	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;
	ID3D11Buffer* _pConstantBuffer;
	float _x, _y, _z;
	float _xAngle, _yAngle, _zAngle;
	float _tX, _tY, _tZ;
	float _t;

public:
	Cube(float x, float y, float z, float xAngle, float yAngle, float zAngle, float tX, float tY, float tZ,
		ID3D11DeviceContext* pImmediateContext, D3D_DRIVER_TYPE driverType, ID3D11VertexShader* pVertexShader, ID3D11PixelShader* pPixelShader, ID3D11Buffer* pConstantBuffer);
	void Draw(XMFLOAT4X4 view, XMFLOAT4X4 projection);
	void Update();
};

