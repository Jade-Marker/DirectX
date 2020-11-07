#include "StructuredBuffer.h"

StructuredBuffer::StructuredBuffer(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const void* pInitialData, int count, int sizeOfElement):
	_pd3dDevice(pd3dDevice), _pImmediateContext(pImmediateContext), _pBuffer(nullptr)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = count * sizeOfElement;
	bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bd.StructureByteStride = sizeOfElement;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pInitialData;

	HRESULT hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &_pBuffer);

	D3D11_SHADER_RESOURCE_VIEW_DESC rvD;
	ZeroMemory(&rvD, sizeof(rvD));
	rvD.Format = DXGI_FORMAT_UNKNOWN;
	rvD.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	rvD.Buffer.ElementOffset = 0;
	rvD.Buffer.ElementWidth = count;
	_pd3dDevice->CreateShaderResourceView(_pBuffer, &rvD, &_pView);

}

void StructuredBuffer::Bind(Shader* shader, UINT slot)
{
	shader->SetShaderResources(slot, 1, &_pView);
}

void StructuredBuffer::Update(const void* pData, UINT size, UINT offset)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(mappedResource));
	_pImmediateContext->Map(_pBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedResource);
	memcpy((void*)((UINT)mappedResource.pData + offset), pData, size);
	_pImmediateContext->Unmap(_pBuffer, 0);
}
