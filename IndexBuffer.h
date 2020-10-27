#pragma once
#include <d3d11.h>
#include "Mesh.h"
class IndexBuffer
{
private:
	ID3D11Device* _pd3dDevice;
	ID3D11DeviceContext* _pImmediateContext;
	ID3D11Buffer* _pIndexBuffer;

public:
	IndexBuffer(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	HRESULT Initialise(Mesh* mesh);
	void Bind();
};

