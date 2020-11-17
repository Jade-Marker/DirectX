#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "ConstantBuffer.h"
#include "RasterState.h"
#include "RenderingBuffers.h"
class Renderer :
	public Component
{
private:
	Mesh* _pMesh;
	Material* _pMaterial;
	ConstantBuffer* _pLocalConstantBuffer;
	RasterState* _pRasterState;
	RenderingBuffers* _pRenderingBuffers;

public:
	Renderer(ConstantBuffer* pLocalConstantBuffer);

	virtual void Start();
	virtual void Draw();
};

