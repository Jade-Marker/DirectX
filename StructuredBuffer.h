#pragma once
#include <d3d11.h>
#include "Shader.h"

class StructuredBuffer
{
private:
	ID3D11Device* _pd3dDevice;
	ID3D11DeviceContext* _pImmediateContext;
	ID3D11Buffer* _pBuffer;
	ID3D11ShaderResourceView* _pView;

public:
	StructuredBuffer(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, const void* pInitialData, int count, int sizeOfElement);

	void Bind(Shader* shader, UINT slot);

	void Update(const void* pData, UINT size, UINT offset);
};

