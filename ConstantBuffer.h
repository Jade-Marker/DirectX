#pragma once
#include "Buffer.h"
class ConstantBuffer : Buffer
{
private:

public:
	HRESULT Initialise(UINT size);
	virtual void Bind(Shader* shader, UINT slot);
	void Update(const void* pData);
};

