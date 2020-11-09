#pragma once
#include <d3d11.h>
#include "Mesh.h"
#include "DeviceManager.h"

class IndexBuffer
{
private:
	ID3D11Buffer* _pIndexBuffer;

public:
	IndexBuffer();
	~IndexBuffer();

	HRESULT Initialise(Mesh* mesh);
	void Bind();
};

