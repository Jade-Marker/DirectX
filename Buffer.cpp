#include "Buffer.h"

Buffer::Buffer():
	_pBuffer(nullptr)
{
}

Buffer::~Buffer()
{
	if (_pBuffer) _pBuffer->Release();
}

HRESULT Buffer::Initialise(UINT ByteWidth, D3D11_USAGE Usage, UINT BindFlags, UINT CPUAccessFlags, UINT MiscFlags, UINT StructureByteStride, const void* pData)
{
	return Initialise(ByteWidth, Usage, BindFlags, CPUAccessFlags, MiscFlags, StructureByteStride, pData, _pBuffer);
}

HRESULT Buffer::Initialise(UINT ByteWidth, D3D11_USAGE Usage, UINT BindFlags, UINT CPUAccessFlags, UINT MiscFlags, UINT StructureByteStride, const void* pData, ID3D11Buffer*& pBuffer)
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = ByteWidth;
	bufferDesc.Usage = Usage;
	bufferDesc.BindFlags = BindFlags;
	bufferDesc.CPUAccessFlags = CPUAccessFlags;
	bufferDesc.MiscFlags = MiscFlags;
	bufferDesc.StructureByteStride = StructureByteStride;

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(subData));
	subData.pSysMem = pData;

	HRESULT hr = DeviceManager::GetDevice()->CreateBuffer(&bufferDesc, &subData, &pBuffer);

	return hr;
}
