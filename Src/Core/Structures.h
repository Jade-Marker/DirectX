#pragma once
#include <DirectXMath.h>
#include <cstring>
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
	XMFLOAT4 DiffuseMtrl;
	XMFLOAT4 AmbientMtrl;
	XMFLOAT4 SpecularMtrl;
};

struct GlobalConstantBuffer
{
	XMMATRIX ViewMatrix;
	XMMATRIX ProjectionMatrix;
	XMFLOAT3 EyePosW;
	float gTime;

	int numLights;
};

struct Transform
{
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;

	Transform(const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& scale)
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;
	}

	Transform()
	{
		Position = XMFLOAT3(0, 0, 0);
		Rotation = XMFLOAT3(0, 0, 0);
		Scale = XMFLOAT3(0, 0, 0);
	}

	void Translate(const XMFLOAT3& translation)
	{
		XMStoreFloat3(&Position, XMLoadFloat3(&Position) + XMLoadFloat3(&translation));
	}

	void Translate(const XMVECTOR& translation)
	{
		XMStoreFloat3(&Position, XMLoadFloat3(&Position) + translation);
	}

	void Rotate(const XMFLOAT3& rotation)
	{
		XMStoreFloat3(&Rotation, XMLoadFloat3(&Rotation) + XMLoadFloat3(&rotation));
	}

	void Rotate(const XMVECTOR& rotation)
	{
		XMStoreFloat3(&Rotation, XMLoadFloat3(&Rotation) + rotation);
	}

	XMMATRIX GetWorldMatrix()
	{
		DirectX::XMMATRIX world =
			DirectX::XMMatrixScalingFromVector(XMLoadFloat3(&Scale)) *
			GetRotationMatrix() *
			DirectX::XMMatrixTranslationFromVector(XMLoadFloat3(&Position)) *
			DirectX::XMMatrixIdentity();

		return world;
	}

	XMMATRIX GetRotationMatrix()
	{
		DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&Rotation));
		return rotation;
	}
};

enum ComponentType
{
	MATERIAL, MESH, RENDERER, RASTER_STATE, ROTATOR, RENDERING_BUFFER, SELECTION_HIDE, CAMERA, DEBUG_CAMERA_CONTROLLER, SCENE_LIGHT, SKYBOX_RASTER_STATE, CUSTOM_COMPONENT, NO_TYPE
};