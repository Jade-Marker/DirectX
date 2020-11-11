#pragma once
#include "Buffer.h"

class StructuredBuffer: Buffer
{
private:
	ID3D11ShaderResourceView* _pView;
	UINT _size;
	UINT _stride;

	void InitializeBuffer(ID3D11Buffer*& pBuffer, ID3D11ShaderResourceView*& pView, const void* pInitialData, int count, int stride);

public:
	StructuredBuffer(const void* pInitialData, int count, int stride);
	~StructuredBuffer();

	virtual void Bind(Shader* shader, UINT slot);

	void Update(const void* pData, UINT size, UINT offset);
};

