#include "RenderingBuffers.h"

RenderingBuffers::RenderingBuffers(ConstantBuffer* pLocalConstantBuffer):
	_pLocalConstantBuffer(pLocalConstantBuffer)
{
}

void RenderingBuffers::Start()
{
	Mesh* pMesh = _pParent->GetComponent<Mesh>();

	_vertexBuffer.Initialise(pMesh);
	_indexBuffer.Initialise(pMesh);

	_pMaterial = _pParent->GetComponent<Material>();
}

void RenderingBuffers::BindBuffers(Shader* shader)
{
	_vertexBuffer.Bind();
	_indexBuffer.Bind();

	LocalConstantBuffer cb;
	cb.WorldMatrix = _pParent->GetWorldMatrix();

	if (_pMaterial)
	{
		cb.DiffuseMtrl = _pMaterial->GetDiffuseMaterial();
		cb.AmbientMtrl = _pMaterial->GetAmbientMaterial();
		cb.SpecularMtrl = _pMaterial->GetSpecularMaterial();
	}
	else
	{
		cb.DiffuseMtrl  =Vector4D(1, 1, 1, 1);
		cb.AmbientMtrl  =Vector4D(1, 1, 1, 1);
		cb.SpecularMtrl =Vector4D(1, 1, 1, 1);
	}

	_pLocalConstantBuffer->UpdateSubresource(&cb);
	_pLocalConstantBuffer->Bind(shader, cLocalConstantBufferSlot);
}