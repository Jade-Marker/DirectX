#pragma once
#include <d3d11.h>
#include "DeviceManager.h"
#include "Shader.h"
class Buffer
{
protected:
	ID3D11Buffer* _pBuffer;

protected:
	HRESULT Initialise(UINT ByteWidth, D3D11_USAGE Usage, UINT BindFlags, UINT CPUAccessFlags, UINT MiscFlags, UINT StructureByteStride, const void* pData, ID3D11Buffer*& pBuffer);

public:
	Buffer();
	~Buffer();

	HRESULT Initialise(UINT ByteWidth, D3D11_USAGE Usage, UINT BindFlags, UINT CPUAccessFlags, UINT MiscFlags, UINT StructureByteStride, const void* pData);

	virtual void Bind(Shader* shader, UINT slot) = 0;
};

