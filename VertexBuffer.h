#pragma once
#include <d3d11.h>
#include "Mesh.h"
#include "DeviceManager.h"

class VertexBuffer
{
private:
	ID3D11Buffer* _pVertexBuffer;
	Mesh* _pMesh;

public:
	VertexBuffer();

	HRESULT Initialise(Mesh* mesh);
	void Bind();
};

