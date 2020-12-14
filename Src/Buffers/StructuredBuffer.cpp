#include "StructuredBuffer.h"

void StructuredBuffer::InitializeBuffer(ID3D11Buffer*& pBuffer, ID3D11ShaderResourceView*& pView, const void* pInitialData, int count, int stride)
{
	HRESULT hr = Buffer::Initialise(count * stride, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 
		D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ, D3D11_RESOURCE_MISC_BUFFER_STRUCTURED, stride, pInitialData, pBuffer);

	D3D11_SHADER_RESOURCE_VIEW_DESC rvD;
	ZeroMemory(&rvD, sizeof(rvD));
	rvD.Format = DXGI_FORMAT_UNKNOWN;
	rvD.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	rvD.Buffer.ElementOffset = 0;
	rvD.Buffer.ElementWidth = count;
	DeviceManager::GetDevice()->CreateShaderResourceView(pBuffer, &rvD, &pView);
}

StructuredBuffer::StructuredBuffer(const void* pInitialData, int count, int stride):
	_pView(nullptr), _size(count * stride), _stride(stride)
{
	InitializeBuffer(_pBuffer, _pView, pInitialData, count, stride);

}

StructuredBuffer::~StructuredBuffer()
{
	if (_pView) _pView->Release();
}

void StructuredBuffer::Bind(Shader* shader, UINT slot)
{
	shader->SetShaderResources(slot, 1, &_pView);
}

void StructuredBuffer::UpdateBuffer(const void* pData, UINT size, UINT offset)
{
	//If trying to update past the end of the buffer, resize it
	if (size + offset > _size)
	{
		ID3D11Buffer* newBuffer;
		ID3D11ShaderResourceView* newView;

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));
		DeviceManager::GetContext()->Map(_pBuffer, 0, D3D11_MAP_READ, 0, &mappedResource);

		//Set size of new buffer to be atleast 2* bigger than current
		UINT factor = (size + offset) / _size;
		factor = max(2, factor);
		_size *= factor;

		//Initialise the new buffer with the data of the old buffer
		InitializeBuffer(newBuffer, newView, mappedResource.pData, _size / _stride, _stride);

		//Delete the old buffer
		DeviceManager::GetContext()->Unmap(_pBuffer, 0);
		_pBuffer->Release();
		_pView->Release();


		_pBuffer = newBuffer;
		_pView = newView;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(mappedResource));
	DeviceManager::GetContext()->Map(_pBuffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedResource);
	memcpy((void*)((UINT)mappedResource.pData + offset), pData, size);
	DeviceManager::GetContext()->Unmap(_pBuffer, 0);
}
