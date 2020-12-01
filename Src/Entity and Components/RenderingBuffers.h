#pragma once
#include "Component.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "Material.h"
class RenderingBuffers :
	public Component
{
private:
	VertexBuffer _vertexBuffer;
	IndexBuffer _indexBuffer;
	ConstantBuffer* _pLocalConstantBuffer;
	Material* _pMaterial;

public:
	RenderingBuffers(ConstantBuffer* pLocalConstantBuffer);

	virtual void Start();
	void BindBuffers(Shader* shader);
};

