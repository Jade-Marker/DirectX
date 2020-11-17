#include "RenderingBuffers.h"

RenderingBuffers::RenderingBuffers(ConstantBuffer* pLocalConstantBuffer):
	_pLocalConstantBuffer(pLocalConstantBuffer)
{
}

void RenderingBuffers::Start()
{
	Mesh* pMesh = _parent->GetComponent<Mesh>();

	_vertexBuffer.Initialise(pMesh);
	_indexBuffer.Initialise(pMesh);
}

void RenderingBuffers::BindBuffers(Shader* shader)
{
	_vertexBuffer.Bind();
	_indexBuffer.Bind();

	LocalConstantBuffer cb;
	cb.WorldMatrix = XMMatrixTranspose(_parent->GetWorldMatrix());
	_pLocalConstantBuffer->Update(&cb);
	_pLocalConstantBuffer->Bind(shader, cLocalConstantBufferSlot);
}