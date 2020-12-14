#include "Buffer.h"

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

	HRESULT hr;
	if (pData == nullptr)
	{
		hr = DeviceManager::GetDevice()->CreateBuffer(&bufferDesc, nullptr, &pBuffer);
	}
	else
	{
		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(subData));
		subData.pSysMem = pData;

		hr = DeviceManager::GetDevice()->CreateBuffer(&bufferDesc, &subData, &pBuffer);
	}

	return hr;
}


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