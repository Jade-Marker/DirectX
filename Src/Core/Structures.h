#pragma once
#include <cstring>
#include <MathLibrary\Vector2D.h>
#include <MathLibrary\Vector3D.h>
#include <MathLibrary\Vector4D.h>
#include <MathLibrary\Matrix.h>
#include <MathLibrary\Constants.h>

#include "Transform.h"

struct BasicVertex
{
	Vector3D Pos;
	Vector4D Color;
};

struct LightVertex
{
	Vector3D Pos;
	Vector3D Normal;
	Vector2D TexCoord;

	bool operator<(const LightVertex other) const
	{
		return memcmp((void*)this, (void*)&other, sizeof(LightVertex)) > 0;
	};
};

__declspec(align(16)) struct LocalConstantBuffer
{
	Matrix WorldMatrix;
	Vector4D DiffuseMtrl;
	Vector4D AmbientMtrl;
	Vector4D SpecularMtrl;
};

__declspec(align(16)) struct GlobalConstantBuffer
{
	Matrix ViewMatrix;
	Matrix ProjectionMatrix;
	Vector3D EyePosW;
	float gTime;


	int numLights;
};

enum ComponentType
{
	MATERIAL, MESH, RENDERER, RASTER_STATE, ROTATOR, RENDERING_BUFFER, SELECTION_HIDE, CAMERA, DEBUG_CAMERA_CONTROLLER, SCENE_LIGHT, SKYBOX_RASTER_STATE, CUSTOM_COMPONENT, PARTICLE_MODEL, NO_TYPE
};