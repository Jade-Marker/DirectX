#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "RasterState.h"
#include "RenderingBuffers.h"
class Renderer :
	public Component
{
private:
	Mesh* _pMesh;
	Material* _pMaterial;
	RasterState* _pRasterState;
	RenderingBuffers* _pRenderingBuffers;

public:
	virtual void Start();
	virtual void Draw();
};

