#include "StructuredBuffer.h"

void StructuredBuffer::InitializeBuffer(ID3D11Buffer*& pBuffer, ID3D11ShaderResourceView*& pView, const void* pInitialData, int count, int stride)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = count * stride;
	bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bd.StructureByteStride = stride;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pInitialData;

	HRESULT hr = _pd3dDevice->CreateBuffer(&bd, &InitData, &pBuffer);

	D3D11_SHADER_RESOURCE_VIEW_DESC rvD;
	ZeroMemory(&rvD, sizeof(rvD));
	rvD.Format = DXGI_FORMAT_UNKNOWN;
	rvD.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	rvD.Buffer.ElementOffset = 0;
	rvD.Buffer.ElementWidth = count;
	_pd3dDevice->CreateShaderResourceView(pBuffer, &rvD, &pView);
}

StructuredBuffer::StructuredBuffer(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const void* pInitialData, int count, int stride):
	_pd3dDevice(pd3dDevice), _pImmediateContext(pImmediateContext), _pBuffer(nullptr), _pView(nullptr), _size(count * stride), _stride(stride)
{
	InitializeBuffer(_pBuffer, _pView, pInitialData, count, stride);

}

void StructuredBuffer::Bind(Shader* shader, UINT slot)
{
	shader->SetShaderResources(slot, 1, &_pView);
}

void StructuredBuffer::Update(const void* pData, UINT size, UINT offset)
{
	if (size + offset > _size)
	{
		ID3D11Buffer* newBuffer;
		ID3D11ShaderResourceView* newView;

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		_pImmediateContext->Map(_pBuffer, 0, D3D11_MAP_READ, 0, &mappedResource);

		UINT factor = (size + offset) / _size;
		factor = max(2, factor);
		_size *= factor;

		InitializeBuffer(newBuffer, newView, mappedResource.pData, _size / _stride, _stride);
		_pImmediateContext->Unmap(_pBuffer, 0);
		_pBuffer->Release();
		_pView->Release();


		_pBuffer = newBuffer;
		_pView = newView;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(mappedResource));
	_pImmediateContext->Map(_pBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedResource);
	memcpy((void*)((UINT)mappedResource.pData + offset), pData, size);
	_pImmediateContext->Unmap(_pBuffer, 0);
}
