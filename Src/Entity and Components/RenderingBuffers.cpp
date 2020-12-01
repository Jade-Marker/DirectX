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

	_pMaterial = _parent->GetComponent<Material>();
}

void RenderingBuffers::BindBuffers(Shader* shader)
{
	_vertexBuffer.Bind();
	_indexBuffer.Bind();

	LocalConstantBuffer cb;
	cb.WorldMatrix = XMMatrixTranspose(_parent->GetWorldMatrix());

	if (_pMaterial)
	{
		cb.DiffuseMtrl = _pMaterial->GetDiffuseMaterial();
		cb.AmbientMtrl = _pMaterial->GetAmbientMaterial();
		cb.SpecularMtrl = _pMaterial->GetSpecularMaterial();
	}
	else
	{
		cb.DiffuseMtrl = XMFLOAT4(1, 1, 1, 1);
		cb.AmbientMtrl = XMFLOAT4(1, 1, 1, 1);
		cb.SpecularMtrl = XMFLOAT4(1, 1, 1, 1);
	}

	_pLocalConstantBuffer->Update(&cb);
	_pLocalConstantBuffer->Bind(shader, cLocalConstantBufferSlot);
}