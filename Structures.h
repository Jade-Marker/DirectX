#pragma once
#include <DirectXMath.h>
using namespace DirectX;

struct BasicVertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct LightVertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;

	bool operator<(const LightVertex other) const
	{
		return memcmp((void*)this, (void*)&other, sizeof(LightVertex)) > 0;
	};
};

struct LocalConstantBuffer
{
	XMMATRIX WorldMatrix;
};

struct GlobalConstantBuffer
{
	XMMATRIX ViewMatrix;
	XMMATRIX ProjectionMatrix;
	XMFLOAT4 DiffuseMtrl;
	XMFLOAT4 DiffuseLight;
	XMFLOAT4 AmbientMtrl;
	XMFLOAT4 AmbientLight;
	XMFLOAT4 SpecularMtrl;
	XMFLOAT4 SpecularLight;
	XMFLOAT3 EyePosW;
	float	 SpecularPower;
	XMFLOAT3 LightVecW;
	float gTime;
};