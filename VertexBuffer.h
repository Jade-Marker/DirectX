#pragma once
#include <d3d11.h>
#include "Mesh.h"
class VertexBuffer
{
private:
	ID3D11Device* _pd3dDevice;
	ID3D11DeviceContext* _pImmediateContext;
	ID3D11Buffer* _pVertexBuffer;
	Mesh* _pMesh;

public:
	VertexBuffer(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	HRESULT Initialise(Mesh* mesh);
	void Bind();
};

